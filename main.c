#include <stdio.h>

//Classe Base: Calculadora

typedef struct Calculadora {
    double (*calcular)(struct Calculadora *this, double a, double b);
    const char *nome;
} Calculadora;


//Classe Derivada: CalcSoma

typedef struct {
    Calculadora base;
} CalcSoma;

double soma_calcular(Calculadora *this, double a, double b) {
    return a + b;
}

double soma_calcular_tres(Calculadora *this, double a, double b, double c) {
    return a + b + c;
}

CalcSoma criar_soma() {
    CalcSoma c;
    c.base.calcular = soma_calcular;
    c.base.nome = "CalcSoma";
    return c;
}


  // Classe Derivada: CalcSubtracao

typedef struct {
    Calculadora base;
} CalcSubtracao;

double sub_calcular(Calculadora *this, double a, double b) {
    return a - b;
}

CalcSubtracao criar_subtracao() {
    CalcSubtracao c;
    c.base.calcular = sub_calcular;
    c.base.nome = "CalcSubtracao";
    return c;
}

   //Classe Derivada: CalcMultiplicacao

typedef struct {
    Calculadora base;
} CalcMultiplicacao;

double mult_calcular(Calculadora *this, double a, double b) {
    return a * b;
}

CalcMultiplicacao criar_multiplicacao() {
    CalcMultiplicacao c;
    c.base.calcular = mult_calcular;
    c.base.nome = "CalcMultiplicacao";
    return c;
}

   //Classe Derivada: CalcDivisao

typedef struct {
    Calculadora base;
} CalcDivisao;

double div_calcular(Calculadora *this, double a, double b) {
    if (b == 0.0) {
        printf("Divisao por zero\n");
        return 0.0;
    }
    return a / b;
}

CalcDivisao criar_divisao() {
    CalcDivisao c;
    c.base.calcular = div_calcular;
    c.base.nome = "CalcDivisao";
    return c;
}


   //Função para calcular e mostrar apenas o resultado

void executar_operacao(Calculadora *calc, double a, double b, char simbolo) {
    double resultado = calc->calcular(calc, a, b);
    
    // Só imprime a equação se não for um erro de divisão por zero
    if (!(simbolo == '/' && b == 0.0)) {
        printf("%.2f %c %.2f = %.2f\n", a, simbolo, b, resultado);
    }
}

int main() {
    // Cria objetos das classes derivadas
    CalcSoma          objSoma = criar_soma();
    CalcSubtracao     objSub  = criar_subtracao();
    CalcMultiplicacao objMult = criar_multiplicacao();
    CalcDivisao       objDiv  = criar_divisao();

    // Mostra resultados de Polimorfismo e Sobrescrita
    executar_operacao((Calculadora*)&objSoma, 15.0, 7.0, '+');
    executar_operacao((Calculadora*)&objSub,  20.0, 8.0, '-');
    executar_operacao((Calculadora*)&objMult, 6.0,  4.0, '*');
    executar_operacao((Calculadora*)&objDiv,  10.0, 2.0, '/');
    executar_operacao((Calculadora*)&objDiv,  10.0, 0.0, '/'); 

    // Mostra resultado
    double a = 10.0, b = 20.0, c = 30.0;
    double res = soma_calcular_tres((Calculadora*)&objSoma, a, b, c);
    printf("%.2f + %.2f + %.2f = %.2f\n", a, b, c, res);

    return 0;
}