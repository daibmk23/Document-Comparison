#include <cstdio>
#include <algorithm>
using namespace std;

static const int MAXN = 100000;
static const int MAXLENGTH = 105;
static const int MAXVAR = 6000; //maximum variants per form

int n;
static char docs[MAXN+1][MAXLENGTH];
int lengths[MAXN+1];

int getStringLength(const char* s) {
    int length = 0;
    while (s[length] != '\0') length++;
    return length;
}

//void toLowerCase(char* s) {
//    int len = getStringLength(s);
//    for (int i = 0; i < len; i++) {
//        if (s[i]>='A' && s[i]<='Z') s[i]+=32;
//    }
//}

int smallestIndexCyclic(const char* s, int strLength) {
    int i = 0;
    int j = 1, x = 0;
    while (i < strLength && j < strLength && x < strLength) {
        char c1 = s[(i + x) % strLength];
        char c2 = s[(j + x) % strLength];
        if (c1 == c2)
        { x++;
            continue;
        }
        if (c1 > c2) {
            i = i + x + 1;
        }
        else {
            j = j + x + 1;
        }
        if (i == j) {
            i++;
        }
        x=0;
    }
    if (i < j){
        return i;
    }
    return j;
}

void minimizedShiftForm(const char* src, char* dst) {
    int len = getStringLength(src);
    int start = smallestIndexCyclic(src, len);
    for (int i = 0; i < len; i++) {
        dst[i] = src[(start + i) % len];
    }
    dst[len] = '\0';//mark end
}

int generateVariants(const char* base, char variants[][MAXLENGTH], int maxVariants) {
    int len = getStringLength(base), count = 0;

    for (int i = 0; (i < len) && (count < maxVariants); i++) {
        int newLen = len - 1;
        for (int j = 0; j < i; j++) {
            variants[count][j]=base[j];
        }
        for (int j=i; j<newLen; j++) {
            variants[count][j] = base[j + 1];
        }
        variants[count][newLen] = '\0';
        count++;
    }

    if (len + 1 < MAXLENGTH) {
        for (int pos = 0; pos <= len && count < maxVariants; pos++) {
            for (int character = 'a'; character <= 'z' && count < maxVariants; character++) {
                int newLen = len+1;
                for (int j = 0; j < pos; j++) {
                    variants[count][j] = base[j];
                }
                variants[count][pos] = (char)character;

                for (int j = pos; j < len; j++){
                    variants[count][j + 1] = base[j];
                }
                variants[count][newLen]='\0';
                count++;
            }
        }
    }

    for (int i = 0; i < len && count < maxVariants; i++) {
        for (int character = 'a'; character <= 'z' && count < maxVariants; character++) {
            if (character == base[i]){
                continue;
            }
            int newLen = len;

            for (int j = 0; j < newLen; j++) {
                variants[count][j] = base[j];
            }
            variants[count][newLen] = '\0';
            variants[count][i] = (char)character;
            count++;
        }
    }

    return count;
}

unsigned long long hash1BASE=131ULL;
unsigned long long hash2BASE=137ULL;
unsigned long long MODULO7 = 1000000007;
unsigned long long MODULO9 = 1000000009;

unsigned long long getHash7(const char* s) {
    unsigned long long h=0ULL;
    for(int i = 0; s[i]; i++){
        h = (h * hash1BASE + (unsigned char)(s[i])) % MODULO7;
    }
    return h;
}
unsigned long long getHash9(const char* s) {
    unsigned long long h = 0ULL;
    for(int i = 0; s[i]; i++){
        h = (h * hash2BASE + (unsigned char)(s[i])) % MODULO9;
    }
    return h;
}

struct stringForm {
    unsigned long long h1,h2;
    int patternIndex; //docum index
};

bool formLess(const stringForm&A, const stringForm&B) {
    if (A.h1 < B.h1) {
        return true;
    }
    if (A.h1 > B.h1) {
        return false;
    }
    return A.h2<B.h2;
}
bool formEqual(const stringForm&A, const stringForm&B) {
    return (A.h1 == B.h1 && A.h2 == B.h2);
}


int parent[MAXN + 1], sizeSet[MAXN + 1];
int findSet(int v) {
    while(v!=parent[v]) v=parent[v];
    return v;
}

void completeSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);

    if (a != b) {
        if(sizeSet[a] < sizeSet[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        parent[b] = a;
        sizeSet[a] += sizeSet[b];
    }
}

static char normalForm[MAXLENGTH];
static char variantsArr[MAXVAR][MAXLENGTH];

int main(int argc, char* argv[]){
    if(argc > 1) {
        freopen(argv[1],"r",stdin);
    }
    if(argc >2) {
        freopen(argv[2],"w",stdout);
    }

    scanf("%d",&n);
    for(int i = 1; i <= n; i++){
        scanf("%s", docs[i]);
        lengths[i] = getStringLength(docs[i]);
    }

    //Case I: minimal forms only
    stringForm* minimalForms = new stringForm[n];
    for(int i = 1;i <= n;i++){
        minimizedShiftForm(docs[i], normalForm);
        unsigned long long h1 = getHash7(normalForm);
        unsigned long long h2 = getHash9(normalForm);

        minimalForms[i - 1].h1 = h1;
        minimalForms[i - 1].h2 = h2;
        minimalForms[i - 1].patternIndex = i;
    }

    for(int i = 1;i <= n;i++){
        parent[i] = i;
        sizeSet[i]=1;
    }

    sort(minimalForms, minimalForms+n, formLess);

    //categorize identical minimal forms
    for(int i = 1;i < n;i++){
        if(formEqual(minimalForms[i], minimalForms[i - 1])) {
            completeSet(minimalForms[i].patternIndex, minimalForms[i - 1].patternIndex);
        }
    }

    // get distinct representatives
    int numberOfDifferentClass = 0;
    static int representativeOf[MAXN];
    for(int i = 1;i <= n;i++){
        if(findSet(i) == i){
            representativeOf[numberOfDifferentClass++] = i;
        }
    }


    //Part2: get the variants from each distinct class representative minimal form
    stringForm* repForms = new stringForm[numberOfDifferentClass * (MAXVAR + 1)];
    int repFormsCount = 0;

    for (int x = 0; x < numberOfDifferentClass; x++){
        int repDoc = representativeOf[x];
        minimizedShiftForm(docs[repDoc], normalForm);
        {
            unsigned long long h1 = getHash7(normalForm);
            unsigned long long h2 = getHash9(normalForm);
            repForms[repFormsCount].h1 = h1;
            repForms[repFormsCount].h2 = h2;
            repForms[repFormsCount].patternIndex = repDoc;
            repFormsCount++;
        }

        int variantsCount = generateVariants(normalForm, variantsArr, MAXVAR);
        for (int v = 0; v < variantsCount; v++) {
            unsigned long long h1 = getHash7(variantsArr[v]);
            unsigned long long h2 = getHash9(variantsArr[v]);
            repForms[repFormsCount].h1 = h1;
            repForms[repFormsCount].h2 = h2;
            repForms[repFormsCount].patternIndex = repDoc;
            repFormsCount++;
        }
    }

    //find the complete set of identical forms again
    sort(repForms, repForms + repFormsCount, formLess);
    for (int i = 1; i < repFormsCount; i++) {
        if(formEqual(repForms[i], repForms[i-1])) {
            completeSet(repForms[i].patternIndex, repForms[i - 1].patternIndex);
        }
    }

    int distinctSetSize  = 0;
    for (int i = 1; i <= n-1; i++) {
        if(findSet(i) == i) {
            distinctSetSize++;
        }
    }

    printf("%d\n", distinctSetSize);

    delete[] minimalForms;
    delete[] repForms;
    return 0;
}
