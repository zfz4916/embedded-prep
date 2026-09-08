void reverseString(char* s, int sSize) {
    char * p = s;   //head
    char * t = s + sSize - 1;   //tail
    char c = '0';   //trans

    int count = sSize / 2;

    while ( count > 0 )  {
        c = p[0];
        p[0] = t[0];
        t[0] = c;

        p++;
        t--;
        count--;

    }

}