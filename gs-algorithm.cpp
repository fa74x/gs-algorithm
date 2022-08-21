#include <stdio.h>
#include <time.h>

typedef struct _rep_free_men_list *freeMenList;

struct _rep_free_men_list {
    int i;
    freeMenList next;
};

freeMenList addToEnd (int n, freeMenList &newNode) {
    newNode = new _rep_free_men_list;
    newNode->i = n;
    newNode->next = NULL;
    return newNode;
}

freeMenList addToTop (int n, freeMenList &nodo) {
    freeMenList newNode = new _rep_free_men_list;
    newNode->i = n;
    newNode->next = nodo;
    return newNode;
}

int main() {
    int n;
    printf("Number of men and women: n = ");
    scanf("%d", &n);


    /* STRUCTURE INITIALIZATION */
    int ManPref[n+1][n+1];
    int WomanPref[n+1][n+1];
    int Ranking[n+1][n+1];
    int Next[n+1];
    int Current[n+1];

    for (int i = 1; i <= n; i++) {
        Next[i] = 1;
        Current[i] = 0;
    }

    freeMenList freeMen = new _rep_free_men_list;
    freeMen->i = 1;
    freeMen->next = NULL;
    freeMenList aux = freeMen;
    for (int i = 2; i <= n; i++) 
        aux = addToEnd(i,aux->next);


    /* INPUT READING */
    printf("\n\nINPUT\n\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("M%d preference number %d: ",i,j);
            scanf("%d", &(ManPref[i][j]));
        }
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("W%d preference number %d: ",i,j);
            scanf("%d", &(WomanPref[i][j]));
        }
    }
    /* PREPARING RANKING MATRIX */
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            Ranking[i][WomanPref[i][j]] = j;
    }


    /* PRINTING OF INPUT DATA */
    printf("\n\nTABLES\n\nMen preferences: \n");
    for (int i = 1; i <= n; i++) {
        printf(" M%d  |  ",i);
        for (int j = 1; j <= n; j++)
            printf("%d  ",ManPref[i][j]);
        printf("\n");
    }
    printf("\nWomen preferences: \n");
    for (int i = 1; i <= n; i++) {
        printf(" W%d  |  ",i);
        for (int j = 1; j <= n; j++)
            printf("%d  ",WomanPref[i][j]);
        printf("\n");
    }
    printf("\n");


    /* ALGORITHM */
    while (freeMen != NULL) {
        int m = freeMen->i;
        int w = ManPref[m][Next[m]];
        if (Current[w] == 0) {
            Current[w] = m;
            freeMenList borrar = freeMen;
            freeMen = freeMen->next;
            delete borrar;
        } else {
            if (Ranking[w][m] < Ranking[w][Current[w]]) {
                int m2 = Current[w];
                Current[w] = m;
                freeMenList borrar = freeMen;
                freeMen = freeMen->next;
                delete borrar;
                freeMen = addToTop(m2,freeMen);
            }
        }
        Next[m] = Next[m] + 1;
    }


    /* PRINTING OF OUTPUT */
    printf("\nOUTPUT\n\n");
    for (int i = 1; i <= n; i++) {
        printf("(M%d,W%d)\n",Current[i],i);
    }
    printf("\n");

    return 0;
}

/*

Initially all m ∈ M and w ∈ W are free
While there is a man m who is free and hasn’t proposed to
every woman w for which (m, w) ∈ F
	Choose such a man m
	Let w be the highest-ranked woman in m’s preference list
	to which m has not yet proposed
	If w is free then
		(m, w) become engaged
	Else w is currently engaged to m
		If w prefers m to m then
			m remains free
		Else w prefers m to m
			(m, w) become engaged
			m becomes free
		Endif
	Endif
Endwhile
Return the set S of engaged pairs

*/

/* 
    random input for n = 4 
    ManPref[1][1] = 1;
    ManPref[1][2] = 2;
    ManPref[1][3] = 3;
    ManPref[1][4] = 4;
    ManPref[2][1] = 4;
    ManPref[2][2] = 2;
    ManPref[2][3] = 3;
    ManPref[2][4] = 1;
    ManPref[3][1] = 3;
    ManPref[3][2] = 4;
    ManPref[3][3] = 1;
    ManPref[3][4] = 2;
    ManPref[4][1] = 1;
    ManPref[4][2] = 4;
    ManPref[4][3] = 2;
    ManPref[4][4] = 3;

    WomanPref[1][1] = 2;
    WomanPref[1][2] = 4;
    WomanPref[1][3] = 3;
    WomanPref[1][4] = 1;
    WomanPref[2][1] = 3;
    WomanPref[2][2] = 2;
    WomanPref[2][3] = 4;
    WomanPref[2][4] = 1;
    WomanPref[3][1] = 4;
    WomanPref[3][2] = 2;
    WomanPref[3][3] = 1;
    WomanPref[3][4] = 3;
    WomanPref[4][1] = 4;
    WomanPref[4][2] = 3;
    WomanPref[4][3] = 1;
    WomanPref[4][4] = 2;

    expected output
    (M4,W1)
    (M1,W2)
    (M3,W3)
    (M2,W4)
    */
