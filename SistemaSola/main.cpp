//TRABALHO DE COMPUTAÇÃO GRAFICA
//FELIPE VOGEL
//FELIPE MACHERT
//DIOGO DINIZ

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "imageloader.h"

GLuint text_sun;
GLuint text_mercurio;
GLuint text_venus;
GLuint text_terra;
GLuint text_lua;
GLuint text_marte;
GLuint text_jupiter;
GLuint text_saturno;
GLuint text_anel;
GLuint text_urano;
GLuint text_netuno;
GLuint text_plutao;
GLUquadric *quad;

GLfloat X = 0.0f;       // Translada para direção x (esquerda ou direita)SS3DSS
GLfloat Y = 0.0f;       // Translada para direção y (cima ou baixo)
GLfloat Z = 0.0f;       // Translada para direção z (in ou out)
GLfloat rotX = 0.0f;    // rotaciona a tela no eixo x
GLfloat rotY = 0.0f;    // rotaciona a tela no eixo y
GLfloat rotZ = 0.0f;    // rotaciona a tela no eixo z
GLfloat rotLx = 0.0f;   // Translada a tela andando com a câmera (esq./dir.)
GLfloat rotLy = 0.0f;   // Translada a tela andando com a câmera (cima/baixo)
GLfloat rotLz = 0.0f;   // Translada a tela andando com a câmera (in/out)
GLint i,rot,j,k,xx,yy,zz, solar=0,anel=0, on=0;
GLfloat ang = 90.0, vel = 0.0;
GLsizei largura=100, altura=100;

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	                                         //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB,                       //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE,             //GL_UNSIGNED_BYTE, because pixels are stored
				                               //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId;                          //Returns the id of the texture
}

void PutPixel(float x,float y,float z, float r, float g, float b){
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    glEnd();
    glFlush();
}

void initRendering() {

    //Texturas
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	quad = gluNewQuadric();

	Image* image = loadBMP("sun.bmp");
	text_sun = loadTexture(image);
	image = loadBMP("mercury.bmp");
	text_mercurio = loadTexture(image);
	image = loadBMP("venus.bmp");
	text_venus = loadTexture(image);
	image = loadBMP("earth.bmp");
	text_terra = loadTexture(image);
    image = loadBMP("moon.bmp");
	text_lua = loadTexture(image);
	image = loadBMP("mars.bmp");
	text_marte = loadTexture(image);
    image = loadBMP("jupiter.bmp");
	text_jupiter = loadTexture(image);
	image = loadBMP("saturnus.bmp");
	text_saturno = loadTexture(image);
	image = loadBMP("saturnusring.bmp");
	text_anel = loadTexture(image);
    image = loadBMP("uranus.bmp");
	text_urano = loadTexture(image);
    image = loadBMP("neptune.bmp");
	text_netuno = loadTexture(image);
    image = loadBMP("pluto.bmp");
	text_plutao = loadTexture(image);
	delete image;
}

void iniciar(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);

      //Iluminação
      GLfloat direcao[] = { 1.0, 1.0, -4.0, 1.0 };
      GLfloat intensidade[] = { 1.0, 1.0, 1.0, 1.0 };
      GLfloat ambiente[] = { 0.0, 0.0, 0.0, 0.0 };

      glEnable(GL_DEPTH_TEST);

       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);

       glLightfv(GL_LIGHT0, GL_POSITION, direcao);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, intensidade);

       glEnable(GL_COLOR_MATERIAL);
       glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

       glEnable(GL_LIGHT0);
       glEnable(GL_LIGHTING);



}

void reshape (int w, int h){

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(50, (GLfloat) w /(GLfloat) h , 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 7.0+rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);

        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);

    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;

    for(i=-10;i<10;i++){
        for(j=-10;j<10;j++){
            for(k=-10;k<10;k++){
                 if((i%2==0)&&(j%2==0)&&(k%2==0)){
            xx=i;
            yy=j;
            zz=k;
            PutPixel(xx,yy,zz,1.0,1.0,1.0);}
            }
        }
    }
    glPopMatrix();

    ang = (ang + vel); //incremeto angular de acordo com a velocidade (botao + ou -)

    //0-SOL
    solar = ang*10; //Variavel solar apenas para o calculo, que de acordo com o angulo estabelecerá a cor na condicional abaixo
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot,0.0f,0.0f,1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, text_sun);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.7,50,50);

    //Luz centrada na posição 0,0,0 para apresentação solar
       glDisable(GL_LIGHT0);
       GLfloat direcao[] = { 0.0, 0.0, 0.0, 1.0 };
       glLightfv(GL_LIGHT0, GL_POSITION, direcao);
       glEnable(GL_LIGHT0);


    glPopMatrix();

    if(on==0){   glEnable(GL_LIGHT0);
                 glEnable(GL_LIGHTING);}

    //1-MERCURIO
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
            glTranslatef(2.0*sin(ang*1.3),  0.0f, 1.0*cos(ang*1.3));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot+0.4,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_mercurio);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.06,30,30);
    glPopMatrix();

    //2-VENUS
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
            glTranslatef(2.5*sin(ang*1.1),0.0f, 1.5*cos(ang*1.1));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot+0.3,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_venus);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.08,30,30);
    glPopMatrix();

    //3-TERRA
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
            glTranslatef(3.0*sin(ang),0.0f, 2.0*cos(ang));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot+0.2,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_terra);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.1,30,30);
    glPopMatrix();

    //3.1-LUA
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
        glTranslatef(3.0*sin(ang),0.0f, 2.0*cos(ang));
        //Em relação a Terra
        glRotatef (ang*1000, 0.0, 1.0, 0.0);
        glTranslatef (0.17, 0.0, 0.0);
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot+0.1,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_lua);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.04,30,30);
    glPopMatrix();

    //4-MARTE
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
            glTranslatef(3.5*sin(ang/1.2),0.0f, 2.5*cos(ang/1.2));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_marte);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.09,30,30);
    glPopMatrix();

    //5-JUPITER
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
        glTranslatef(4.5*sin(ang/1.4),0.0f, 3.5*cos(ang/1.4));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot-0.1,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_jupiter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.30,30,30);
    glPopMatrix();

    //6-SATURNO
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
            glTranslatef(5.5*sin(ang/1.6),0.0f, 4.5*cos(ang/1.6));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot-0.2,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_saturno);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.32,30,30);
    glPopMatrix();

    //Anel de Saturno
    anel = ang*5; //Variavel anel apenas para o calculo, que de acordo com o angulo estabelecerá a cor na condicional abaixo
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;

        glTranslatef(5.5*sin(ang/1.6),0.0f, 4.5*cos(ang/1.6));
        glScalef(1.0,0.25,1.0);
            glColor3f (0.8, 0.8, 0.5);
            glRotatef (100, 1.0,0.0,0.0);
            glutSolidTorus(0.1, 0.5, 10, 30);
    glPopMatrix();

    //7-URANO
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
            glTranslatef(6.5*sin(ang/2.0),0.0f, 5.5*cos(ang/2.0));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot-0.3,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_urano);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.14,30,30);
    glPopMatrix();

    //8-NETUNO
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
            glTranslatef(7.0*sin(ang/2.2),0.0f, 6.0*cos(ang/2.2));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot-0.4,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_netuno);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.15,30,30);
    glPopMatrix();

    //9-PLUTÃO
    glPushMatrix();
            glRotatef(rotX,1.0,0.0,0.0);    // Rotaciona em x
            glRotatef(rotY,0.0,1.0,0.0);    // Rotaciona em y
            glRotatef(rotZ,0.0,0.0,1.0);    // Rotaciona em z
            glTranslatef(X, Y, Z); 	        // Translada em x,y,z;
            glTranslatef(8.0*sin(ang),0.0f, 7.0*cos(ang));
        glRotatef(-90,1.0f,0.0f,0.0f);
        glRotatef(rot-0.5,0.0f,0.0f,1.0f);
        glBindTexture(GL_TEXTURE_2D, text_plutao);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gluQuadricTexture(quad,1);
        gluSphere(quad,0.1,30,30);
    glPopMatrix();

    rot=rot+1;
glDisable(GL_TEXTURE_2D);
    glutPostRedisplay();
    glutSwapBuffers();
}


void keyboard (unsigned char key, int x, int y){
    switch (key) {
        case '-':   // Velocidade
            vel += -0.0033;
            break;
        case '+':   // Velocidade
            vel -= -0.0033;
            break;
        case 'x':   // Rotaciona X
            rotX -= 0.5f;
            break;
        case 'X':   // Rotaciona X
            rotX += 0.5f;
            break;
        case 'y':   // Rotaciona Y
            rotY -= 0.5f;
            break;
        case 'Y':   // Rotaciona Y
            rotY += 0.5f;
            break;
        case 'z':   // Rotaciona Z
            rotZ -= 0.5f;
            break;
        case 'Z':   // Rotaciona Z
            rotZ += 0.5f;
            break;
        // j,J,k,K,l,L navega com a camera
        case 'h':      //Camera anda para a esquerda
            rotLx -= 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 7.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        break;
        case 'H':     //Camera anda para a direita
            rotLx += 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 7.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'j':     //Camera anda para a baixo
            rotLy -= 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 7.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'J':     //Camera anda para cima
            rotLy += 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 7.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'k':     //Camera anda para frente
            rotLz -= 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 7.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'K':     //Camera anda para tras
            rotLz += 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 7.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'l':
        case 'L':
          if(on==1)  on=0;
          else on=1;
		break;
        case 'o': //Zera todas as transformações
        case 'O':
            X = Y = 0.0f;
            Z = 0.0f;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
            rotLx = 0.0f;
            rotLy = 0.0f;
            rotLz = 0.0f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(rotLx, rotLy, 7.0f + rotLz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
            break;
      }
      glutPostRedisplay();
}

void specialKey(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT :    // Translada em -X
            X += 0.1f;
            break;
        case GLUT_KEY_RIGHT :   // Translada em X
            X -= 0.1f;
            break;
        case GLUT_KEY_UP :      // Translada em Y
            Y -= 0.1f;
            break;
        case GLUT_KEY_DOWN :    // Translada em -Y
            Y += 0.1f;
            break;
        case GLUT_KEY_PAGE_UP:  // Translada em -Z
            Z += 0.1f;
            break;
        case GLUT_KEY_PAGE_DOWN:// Translada em Z
            Z -= 0.1f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow ("SI - TRABALHO 2ºBIM - SISTEMA SOLAR 3D");
    iniciar();
    initRendering();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutMainLoop();
    return 0;
}
