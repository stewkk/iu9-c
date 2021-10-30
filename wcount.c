
#include <stdio.h>
#include <ctype.h>

int wcount(char* s) {
    if (s[0] == '\0') {
        return 0;
    }
    int ans = 0;
    int index = 1;
    while (s[index] != '\0') {
        if (isspace(s[index]) && !isspace(s[index - 1])) {
            ans++;
        }
        index++;
    }
    if (!isspace(s[index - 1])) {
        ans++;
    }
    return ans;
}

int main() {
    char str[BUFSIZ];
    fgets(str, BUFSIZ, stdin);
    int ans = wcount(str);
    printf("%d\n", ans);
    return 0;
}
