#include<stdio.h>

#define MAX_NODES 1024
#define INFINITY 1000000000
int n, dist[MAX_NODES][MAX_NODES];

struct state {
	int predecessor;
	int length;
	enum {permanent, tentative} label;
} state[MAX_NODES];

void init_state(struct state *p) {
	p->predecessor = -1;
	p->length = INFINITY;
	p->label = tentative;
}

void shortest_path(int from, int to, int path[]) {
	struct state *p;

	for(p = &state[0]; p < &state[n]; ++p) {
		init_state(p);	
	}
	state[from].length = 0; state[from].label = permanent;
	int k = from;
	do {
		for (int i = 0; i < n; i++) {
			if (dist[k][i] != 0 && state[i].label == tentative) {
				if (state[k].length + dist[k][i] < state[i].length) {
					state[i].predecessor = k;
					state[i].length = state[k].length + dist[k][i];
				}
			}
		}

		k = 0; 
		int min = INFINITY;
		for (int i = 0; i < n; i++) {
			if (state[i].label == tentative && state[i].length < min) {
				min = state[i].length;
				k = i;
			}
		}
		state[k].label = permanent;
	} while (k != to);

	k = to;
	int i = 0;
	do {
		path[i++] = k; k = state[k].predecessor;
	} while (k >= 0);
}

int main() {
	
	return 0;
}
