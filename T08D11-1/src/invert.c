#define M(x) if(#x == "int") printf("int")

int main() {
    M(double);
    return 0;
}
