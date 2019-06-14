#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>

#define PAGE_SIZE  256
#define FRAME_SIZE  256


static struct
{
	unsigned int num_page_fault;
	unsigned int num_page_try;
	unsigned int num_tlb_miss;
	unsigned int num_tlb_try;
} perf_stat = {
	.num_page_fault = 0,
	.num_page_try = 0,
	.num_tlb_miss = 0,
	.num_tlb_try = 0
};

struct tlb_entry
{
	uint8_t page_num;
	uint8_t frame_num;
	int is_valid; // 1 is valid or not.
};

struct page_entry
{
	uint16_t frame_num;
	int is_valid; // 1 is valid or not.
};

uint8_t lookup_tlb(uint8_t page_num);
uint8_t lookup_page_table(uint8_t page_num);
uint8_t lookup_phy_mem(uint32_t phy_addr);

void page_fault_handler(uint8_t page_num);
uint32_t to_phy_addr(uint32_t virt_addr);

struct tlb_entry tlb[16];
int tlb_fifo_idx = 0;
struct page_entry page_table[256];
uint8_t phy_mem[256 * 256] = {0,};
uint8_t FRAME_NUM = 0;

int main(int argc, char** argv)
{
	// Clean tlb and page table.
	for (int it = 0; it < 16; ++it) {
		tlb[it].is_valid = 0;
	}
	for (int it = 0; it < 256; ++it) {
		page_table[it].is_valid = 0;
	}

	uint32_t virt_addr;
	while (scanf("%u", &virt_addr) != EOF) {
		uint32_t phy_addr = to_phy_addr(virt_addr);

		fprintf(stderr, "%d\n", lookup_phy_mem(phy_addr));
	}

	printf("pf: %lf\ntlb: %lf\n",
			(double)perf_stat.num_page_fault / perf_stat.num_page_try,
			(double)perf_stat.num_tlb_miss / perf_stat.num_tlb_try);

	return 0;
}

uint8_t lookup_tlb(uint8_t page_num)
{
	perf_stat.num_tlb_try++;

	for (struct tlb_entry* it = tlb;
			it < tlb + 16;
			it++) {
		if (it->is_valid && it->page_num == page_num) {	//tlb hit
			return it->frame_num;
		}
	}

	perf_stat.num_tlb_miss++;

	uint8_t frame_num = lookup_page_table(page_num);

	struct tlb_entry* it = tlb + tlb_fifo_idx;
	tlb_fifo_idx = ++tlb_fifo_idx % 16;

	it->page_num = page_num;
	it->frame_num = frame_num;
	it->is_valid = 1;

	return it->frame_num;
}

uint8_t lookup_page_table(uint8_t page_num)
{
	if (!page_table[page_num].is_valid) {	//page_fault
		page_fault_handler(page_num);
		perf_stat.num_page_fault++;
	}

	assert(page_table[page_num].is_valid);

	perf_stat.num_page_try++;

	return page_table[page_num].frame_num;
}

void page_fault_handler(uint8_t page_num)
{
	FILE* disk_fp = fopen("./input/BACKINGSTORE.bin", "r");

	uint8_t DATA[PAGE_SIZE];
	int a;
	//disk에서 page_num번 째 page 불러오기
	fseek(disk_fp, page_num * PAGE_SIZE, SEEK_SET);
	size_t offset = 0;

	while(offset < PAGE_SIZE)
	{
		offset += fread(DATA + offset, sizeof(uint8_t), PAGE_SIZE - offset, disk_fp);
	}

	//full frame
	if(FRAME_NUM == FRAME_SIZE)
		FRAME_NUM = 0;

	// phy_mem의 frame 등록(빈 frame이 있는 경우)
	for(a = 0; a < PAGE_SIZE; a++)
	{
		phy_mem[FRAME_NUM * PAGE_SIZE + a] = DATA[a];
	}

	// page table에 frame_num 기록
	page_table[page_num].frame_num = FRAME_NUM;
	FRAME_NUM++;

	// 채우고 "is_valid: 1"로
	page_table[page_num].is_valid = 1;

	fclose(disk_fp);
}

uint32_t to_phy_addr(uint32_t virt_addr)
{

	uint32_t Phy_addr = 0;
	uint8_t Page_num;

	//bit masking
	size_t addr_offset = 0;

	for(int a = 1; a < 9; a++)	//offset
	{
		if(virt_addr & a)
			addr_offset |= (uint8_t)pow(2, a-1);
	}
	for(int b = 9; b < 17; b++)	//page_num
	{
		int n;
		if(virt_addr & b){
			n = b - 9;
			Page_num |= (uint8_t)pow(2, n-1);
		}	
	}


	uint8_t Frame_num = lookup_tlb(Page_num);

	//phy_addr = frame_num + offset
	Phy_addr = addr_offset;
	for(int c = 1; c < 9; c++)	//confirm frame_num bit
	{
		if(Frame_num & c)
			Phy_addr |= (uint32_t)pow(2, c+8);
	}

	return Phy_addr; 
}

uint8_t lookup_phy_mem(uint32_t phy_addr)
{
	uint8_t Frame_num;

	//bit masking
	size_t addr_offset = 0;

	for(int a = 1; a < 9; a++)	//offset
	{
		if(phy_addr & a)
			addr_offset |= (uint8_t)pow(2, a-1);
	}
	for(int b = 9; b < 17; b++)	//Frame_num
	{
		int n;
		if(phy_addr & b){
			n = b - 9;
			Frame_num |= (uint8_t)pow(2, n-1);
		}	
	}	

	return phy_mem[FRAME_SIZE*Frame_num + addr_offset]; 
}
