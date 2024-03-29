#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <sys/queue.h>

static LIST_HEAD(listhead, entry) head;

struct listhead *headp = NULL;
int num_entries = 0;

struct entry {
	char name[BUFSIZ];
	int frequency;
	LIST_ENTRY(entry) entries;
};

/*
#define total_thread 29856;
#define BLOCK_SIZE 23134;

pthread_t prepocess_t[total_thread];

void *preprocess_thread(void *arg)
{

int thread_num = *((int *)arg)

fseek(fp, thread_num * BLOCK_SIZE, SEEK_SET);
//파일의 특정위치를 읽는다.

while (fgets(buf, 4096, fp)) {
// Preprocess: change all non-alnums into white-space,
//             alnums to lower-case.
int line_length = strlen(buf);

for (int it = 0; it < line_length; ++it) {
if (!isalnum(buf[it])) {
buf[it] = ' ';
} else {
buf[it] = tolower(buf[it]);
}
}

// 특정 위치에 파일을 저장한다.
fseek(fp2, thread_num * BLOCK_SIZE, SEEK_SET);
offset = 0;
while(offset < BLOCK_SIZE)
{
offset += write(fp2, DATA + offset, BLOCK_SIZE - offset);
}

}

int main(int argc, char** argv)
{
void *thread_return;
FILE* fp = fopen("test.txt", "r");
FILE* fp2 = fopen("pipe_txt", "rw");
char buf[4096];

for()
pthread_create(&prepocess_t[a], NULL, preprocess_thread, (void *)&threadnum);

for()
pthread_join(prepocess_t[b], &thread_return);

fclose(fp);
fclose(fp2);
return 0;
}
 */


int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, "%s: not enough input\n", argv[0]);
		exit(1);
	}

	FILE* fp = fopen(argv[1], "r");
	char buf[4096];

	LIST_INIT(&head);

	while (fgets(buf, 4096, fp)) {
		// Preprocess: change all non-alnums into white-space,
		//             alnums to lower-case.
		int line_length = strlen(buf);

		for (int it = 0; it < line_length; ++it) {
			if (!isalnum(buf[it])) {
				buf[it] = ' ';
			} else {
				buf[it] = tolower(buf[it]);
			}
		}

		// Tokenization
		const char* WHITE_SPACE =" \t\n";
		char* tok = strtok(buf, WHITE_SPACE);

		if (tok == NULL || strcmp(tok, "") == 0) {
			continue;
		}

		do {
			if (num_entries == 0) {
				struct entry* e = malloc(sizeof(struct entry));

				strncpy(e->name, tok, strlen(tok));
				e->frequency = 1;

				LIST_INSERT_HEAD(&head, e, entries);
				num_entries++;
				continue;
			} else if (num_entries == 1) {
				int cmp = strcmp(tok, head.lh_first->name);

				if (cmp == 0) {
					head.lh_first->frequency++;
				} else if (cmp > 0) {
					struct entry* e = malloc(sizeof(struct entry));

					strncpy(e->name, tok, strlen(tok));
					e->frequency = 1;


					LIST_INSERT_AFTER(head.lh_first, e, entries);
					num_entries++;
				} else if (cmp < 0) {
					struct entry* e = malloc(sizeof(struct entry));

					strncpy(e->name, tok, strlen(tok));
					e->frequency = 1;

					LIST_INSERT_HEAD(&head, e, entries);
					num_entries++;
				}

				continue;
			}

			// Reduce: actual word-counting
			struct entry* np = head.lh_first;
			struct entry* final_np = NULL;

			int last_cmp = strcmp(tok, np->name);

			if (last_cmp < 0) {
				struct entry* e = malloc(sizeof(struct entry));

				strncpy(e->name, tok, strlen(tok));
				e->frequency = 1;

				LIST_INSERT_HEAD(&head, e, entries);
				num_entries++;

				continue;

			} else if (last_cmp == 0) {
				np->frequency++;

				continue;
			}

			for (np = np->entries.le_next; np != NULL; np = np->entries.le_next) {
				int cmp = strcmp(tok, np->name);

				if (cmp == 0) {
					np->frequency++;
					break;
				} else if (last_cmp * cmp < 0) { // sign-crossing occurred
					struct entry* e = malloc(sizeof(struct entry));

					strncpy(e->name, tok, strlen(tok));
					e->frequency = 1;

					LIST_INSERT_BEFORE(np, e, entries);
					num_entries++;

					break;
				}

				if (np->entries.le_next == NULL) {
					final_np = np;
				} else {
					last_cmp = cmp;
				}
			}

			if (!np && final_np) {
				struct entry* e = malloc(sizeof(struct entry));

				strncpy(e->name, tok, strlen(tok));
				e->frequency = 1;

				LIST_INSERT_AFTER(final_np, e, entries);
				num_entries++;
			}
		} while (tok = strtok(NULL, WHITE_SPACE));
	}

	// Print the counting result very very slow way.
	int max_frequency = 0;

	for (struct entry* np = head.lh_first; np != NULL; np = np->entries.le_next) {
		if (max_frequency < np->frequency) {
			max_frequency = np->frequency;
		}
	}

	for (int it = max_frequency; it > 0; --it) {
		for (struct entry* np = head.lh_first; np != NULL; np = np->entries.le_next) {
			if (np->frequency == it) {
				printf("%s %d\n", np->name, np->frequency);
			}
		}
	}

	// Release
	while (head.lh_first != NULL) {
		LIST_REMOVE(head.lh_first, entries);
	}

	fclose(fp);

	return 0;
}
