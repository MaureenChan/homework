void func(char str_arg[2]){
    int m = sizeof(str_arg);
    int n = strlen(str_arg);
    printf("%d\n", m);
    printf("%d\n", n);
}

int main(void){
    char str[] = "hello";
    func(str);
}
