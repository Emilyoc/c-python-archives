#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define numIt 1000

double dt = 0.01, w0 = 1.00, wE = 1.00, l = 10.00, g = 9.80665, pi = 3.1415;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void iniciagraf(GLFWwindow* window) {
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void terminagraf(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

double conversaoGrauRadiano(double ag) {
    double o;

    o = (pi * ag) / 180;

    return o;
}

double calculoAceleracao(double A, double f, double V, double t, char c) {
    double a = 0.0, C = 0.05, f0 = 1.00, W;

    W = conversaoGrauRadiano(wE * t);

    if(c == 'c') {  // com forças externas
        a = -1 * (A * f) - (C * V) - (f0 * sin(W));
        //printf("%lf a\n", a);

        } else if(c == 's') { // sem forças externas
            a = -1 * (A * f);
        }
    return a;
}

int main(){
    int i, resp;
    char resp2;
    double X, V, a, A, f;
    double x = 0.5, v = 10.00, o, w, ang = 1.00, vang = 1.00, t, ft, fX;

    o = conversaoGrauRadiano(ang);
    w = conversaoGrauRadiano(vang);

    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if(!glfwInit()) {
        printf("inicialization failed\n");
    }

    window = glfwCreateWindow(640, 480, "Dinamica Molecular", NULL, NULL);

    if(!window) {
        printf("creating window failed\n");
        glfwDestroyWindow(window);
        exit(EXIT_FAILURE);
    }

    do {
        printf("deseja observar o sistema massa-mola(1) ou o pendulo simples(2)?\n");
        scanf("%d", &resp); fflush(stdin);
        if((resp != 1) && (resp != 2)) printf("resposta invalida, digite novamente\n");
    }while((resp != 1) && (resp != 2));

    do {
        printf("deseja observa-lo com forcas externas(c) ou sem forcas externas(s)?\n");
        scanf("%c", &resp2);
        if((resp2 != 'c') && (resp2 != 's')) printf("resposta invalida, digite novamente\n");
    }while((resp2 != 'c') && (resp2 != 's'));

    if(resp == 1) {
        X = x;
        V = v;
    } else if(resp == 2) {
        X = o;
        V = w;
    }

    iniciagraf(window);

    while (!glfwWindowShouldClose(window)) {

        for(i = 0; i < numIt; i++) {

            t = i * dt;

            if(resp == 1) {
                A = w0 * w0;
                f = X;
            } else if(resp == 2) {
                A = g / l;
                f = sin(X);
            }

            a = calculoAceleracao(A, f, V, t, resp2);
            V = V + a * dt;
            X = X + V * dt;

            ft = t / 10 - 1;
            fX = X / 10;

            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(5);

            glBegin(GL_LINES);
            glColor3f(1, 1, 1);
            glVertex3d(0, 1, 0);
            glVertex3d(0,-1, 0);
            glVertex3d(1, 0, 0);
            glVertex3d(-1, 0, 0);

            glBegin(GL_POINTS);
            glColor3f(1, 0, 0);
            glColor3f(0, 1, 0);

            glBegin(GL_POINTS);
            glVertex2d(ft, fX);


            glEnd();

            glfwSwapBuffers(window);
            glfwPollEvents();

        }

    }

    terminagraf(window);

    return 0;

}







