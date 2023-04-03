//LUIS FREDY HUACHACA VARGAS
#include <iostream>
#include <vector>
#include <math.h>

#include <cmath>
#include <chrono>
#include <thread>
#include <string>
using namespace std;

void clear_screen()
{
    cout << "\033[2J\033[H";
    cout.flush();
}

struct Point{
    float x;
    float y;
    Point(float x, float y)
        : x(x), y(y){}
    Point(){};
    void print(){
        cout << x << ", " << y << endl;
    }
    void set_x(float x_){
        x = x_;
    }
    void set_y(float y_){
        this->y = y_;
    }
  
};
struct point3d{
    float x;
    float y;
    float z;

    
};
point3d restarPto(point3d p1,point3d p2){
    point3d res;
    res.x = p1.x-p2.x;
    res.y = p1.y-p2.y;
    res.z = p1.z-p2.z;
    return res;
    }
struct Square{
    Point PointA;
    Point PointB;
    Point PointC;
    Point PointD;
    Square(Point PointA, Point PointB, Point PointC, Point PointD)
    :   PointA(PointA), PointB(PointB), PointC(PointC), PointD(PointD){};
    Square(){};
    void setPoints(vector<Point> points){
        vector<Point> ownPoints  = {PointA, PointB, PointC, PointD};
        for(int i = 0; i < 4; i++){
            ownPoints[i].x = points[i].x;
            ownPoints[i].y = points[i].y;
            //cout << ownPoints[i].x << ", " << ownPoints[i].y << endl;
        }
    }
    void printPoints(){
        vector<Point> points = {PointA, PointB, PointC,PointD};
        for(int i = 0; i<4;i++){
            points[i].print();
        }
    }
    void operations(float op, char mov){
        vector<Point *> points = {&PointA, &PointB, &PointC, &PointD};
        //cout << "axes: " << endl;
        //cout << (mov=='x')<< endl;
        //cout << (mov=='y') << endl;
        if(mov == 'x'){
            for(int a = 0; a < 4; a++) {
                points[a]->set_x(points[a]->x + op);

            }
        }
        if(mov == 'y'){
            for(int a = 0 ; a < 4; a++){
                points[a]->set_y(points[a]->y + op); 
            }
        }
    }
};

void ValidateLine(Point a,Point b, float grilx, float grily, vector<vector<char>> &grill){
    
    if ((((((a.y-b.y)/(a.x-b.x))*(grilx - b.x))-(grily - b.y)) >= -1) && (((((a.y-b.y)/(a.x-b.x))*(grilx - b.x))-(grily - b.y)) <= 1)){
        grill[grilx][grily] = '*';
    }

}
float gety(Point A, Point B, float itr, float scala){
    return ((((A.y*scala)-(B.y*scala))/((A.x*scala) - (A.y*scala)))*(itr - (A.x*scala))) + (A.y*scala); 
}
float getx(Point A, Point B, float itr,float scala){
    return (A.x*scala) + ((itr - (A.y*scala))/(((A.y*scala)-(B.y*scala))/((A.x*scala)-(B.x*scala))));
}


class Cubo{
    public:
    Square a;
    Square b;
    Cubo(){};
    Cubo(Square _a, Square _b){
        a = _a; b = _b;
    };
    void print(){
        cout << "cuboxys" << endl;
        a.printPoints();
        b.printPoints();
        cout << endl;
    };
    void movey(float op){
        a.operations(op,'y');
        b.operations(op,'y');
    }
    void movex(float op){
        a.operations(op,'x');
        b.operations(op,'x');
    }
    void routine(){
        vector<float> vscala={1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.7,1.6,1.5,1.4,1.3,1.2,1.1,1,0.9};
        vector<float> rutax={1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1};
        vector<float> rutay={1,1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1};
        //while(true){
        for(int i=0; i<4; i){
        clear_screen();

        for(int i = 0; i < rutax.size(); i++){
            this->movex(rutax[i]);
            this->movey(rutay[i]);
            //render();
            render(vscala[i]);

            //ver que donde ir al frente y donde ir atras achicar y agrandar
            cout.flush();
            //getchar();
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        }
        
    }
     
    void render(float scala){
        // aqui definimos las lineas que queremos dibujar, damos el a1->a2
        // linea arriba primer cuadrado
        //a.printPoints();
        //b.printPoints();
        vector<char> row;
        row.assign(30,' ');
        // get y es la que me da y despues de darle un x, calulando la formula desde su funcion.
        vector<vector<char>> grill;
        grill.assign(30,row);
        
        //2C - AB
        for(float i = b.PointA.x*scala; i <= b.PointB.x*scala; i++){
            grill[floor(gety(b.PointB,b.PointA, i, scala))][i] = '_';
        }
        // 2C - BC
        for(float j = b.PointB.y*scala; j <= b.PointD.y*scala; j++){
            grill[j][floor(getx(b.PointB,b.PointD,j, scala))] = '_';
        }
        // 2C - CD
        for(float k = b.PointD.x*scala; k >= b.PointC.x*scala; k--){
            grill[floor(gety(b.PointC,b.PointD,k, scala))][k] = '|';
        }
        
        //2C - CA
        for(float l = b.PointC.y*scala; l >= b.PointA.y*scala; l--){
            //cout << "xcor, "<< floor(getx(b.PointA,b.PointB,l))<<endl;
            grill[l][floor(getx(b.PointC,b.PointA,l, scala))] = '|';
        }
        //1c
        //2C - AB
        //cout << "[rtpon]"<< endl;
        //a.PointA.print();
        //a.PointB.print();
        for(float i = a.PointA.x*scala; i <= a.PointB.x*scala; i++){
            grill[floor(gety(a.PointB,a.PointA, i, scala))][i] = '_';
        }
        // 2C - BC
        for(float j = a.PointB.y*scala; j <= a.PointD.y*scala; j++){
            grill[j][floor(getx(a.PointB,a.PointD,j, scala))] = '_';
        }
        // 2C - CD
        
        for(float k = a.PointD.x*scala; k >= a.PointC.x*scala; k--){
            grill[floor(gety(a.PointC,a.PointD,k, scala))][k] = '|';
        }
        
        //2C - CA
        for(float l = a.PointC.y*scala; l >= a.PointA.y*scala; l--){
            //cout << "xcor, "<< floor(getx(b.PointA,b.PointB,l))<<endl;
            grill[l][floor(getx(a.PointC,a.PointA,l, scala))] = '|';
        }
        // aqui pintamos las  diagonales dando definido parametro, se pintara corroborando la linea que si pertenece a la ecuacion con el punto a y el punto b
        //a1 -> a2
        for(float z = b.PointA.y*scala; z <= a.PointA.y*scala;z++){
            grill[z][floor(getx(b.PointA,a.PointA,z, scala))] = '-';
        }
        //b1 -> b2
        for(float q = b.PointB.y*scala; q <= a.PointA.y*scala;q++){
            grill[q][floor(getx(a.PointB,b.PointB,q, scala))] = '-';
            
        }
       
        //c1 - > c2
        for(float h = b.PointC.y*scala; h <= a.PointC.y*scala;h++){
            grill[h][floor(getx(b.PointC,a.PointC,h, scala))] = '-';
            
        }
        for(float m = b.PointD.y*scala; m <= a.PointD.y*scala;m++){
            grill[m][floor(getx(b.PointD,a.PointD,m, scala))] = '-';
            
        }
        

       
        string red = "\033[1;31m"; // red color code
        string reset = "\033[0m"; // reset color code


        for(int ii = 0; ii < 30; ii++){
            for(int jj = 0; jj < 30; jj++){
                cout << red <<grill[ii][jj] <<reset << '\t';
            }
            cout << endl;
        }
        
    }
    

           
};



/*
void GetLinesSquares(Square sA, Square sB){
    // aqui definimos las lineas que queremos dibujar, damos el a1->a2
    // linea arriba primer cuadrado
    sA.printPoints();
    cout << "sA" <<endl;
    sB.printPoints();
    vector<char> row;
    row.assign(30,' ');
    // get y es la que me da y despues de darle un x, calulando la formula desde su funcion.
    vector<vector<char>> grill;
    grill.assign(30,row);

    //2C - AB
    for(float i = sB.PointA.x; i <= sB.PointB.x; i++){
        grill[floor(gety(sB.PointB,sB.PointA, i))][i] = '*';
    };
    // 2C - BC
    for(float j = sB.PointB.y; j <= sB.PointD.y; j++){
        grill[j][floor(getx(sB.PointB,sB.PointD,j))] = '*';
    };
    // 2C - CD
    for(float k = sB.PointD.x; k >= sB.PointC.x; k--){
        grill[floor(gety(sB.PointC,sB.PointD,k))][k] = '*';
    };
    
    //2C - CA
    for(float l = sB.PointC.y; l >= sB.PointA.y; l--){
        //cout << "xcor, "<< floor(getx(sB.PointA,sB.PointB,l))<<endl;
        grill[l][floor(getx(sB.PointC,sB.PointA,l))] = '*';
    };
    //1c
    //2C - AB
    cout << "[rtpon]"<< endl;
    sA.PointA.print();
    sA.PointB.print();
    for(float i = sA.PointA.x; i <= sA.PointB.x; i++){
        grill[floor(gety(sA.PointB,sA.PointA, i))][i] = '*';
    };
    // 2C - BC
    for(float j = sA.PointB.y; j <= sA.PointD.y; j++){
        grill[j][floor(getx(sA.PointB,sA.PointD,j))] = '*';
    };
    // 2C - CD
    
    for(float k = sA.PointD.x; k >= sA.PointC.x; k--){
        grill[floor(gety(sA.PointC,sA.PointD,k))][k] = '*';
    };
    
    //2C - CA
    for(float l = sA.PointC.y; l >= sA.PointA.y; l--){
        //cout << "xcor, "<< floor(getx(sB.PointA,sB.PointB,l))<<endl;
        grill[l][floor(getx(sA.PointC,sA.PointA,l))] = '*';
    };
    // aqui pintamos las  diagonales dando definido parametro, se pintara corroborando la linea que si pertenece a la ecuacion con el punto a y el punto b
    //a1 -> a2
    for(float z = sB.PointA.y; z <= sA.PointA.y;z++){
        grill[z][floor(getx(sB.PointA,sA.PointA,z))] = '-';
    }
    //b1 -> b2
    for(float q = sB.PointB.y; q <= sA.PointA.y;q++){
        grill[q][floor(getx(sA.PointB,sB.PointB,q))] = '-';
        
    }
    cout << "[rtpon]"<< endl;
    sA.PointB.print();
    sB.PointB.print();
    //c1 - > c2
    for(float h = sB.PointC.y; h <= sA.PointC.y;h++){
        grill[h][floor(getx(sB.PointC,sA.PointC,h))] = '-';
        
    }
    for(float m = sB.PointD.y; m <= sA.PointD.y;m++){
        grill[m][floor(getx(sB.PointD,sA.PointD,m))] = '-';
        
    }
    for(int ii = 0; ii < 30; ii++){
        for(int jj = 0; jj < 30; jj++){
            cout << grill[ii][jj] << '\t';
        }
        cout << endl;
    }

    
}
*/

void setView(){

    

    point3d A;A.x = 1;A.y = 1,A.z = 1;
    point3d B;B.x = -1;B.y = 1,B.z = 1;
    point3d C;A.x = 1;C.y = -1,C.z = 1;
    point3d D;D.x = -1;D.y = -1,D.z = 1;
    point3d E;E.x = 1;E.y = 1,E.z = -1;
    point3d F;F.x = -1;F.y = 1,F.z = -1;
    point3d G;G.x = 1;G.y = -1,G.z = -1;
    point3d H;H.x = -1;H.y = -1,H.z = -1;
    vector<point3d> I = {A,B,C,D,E,F,G,H};
    point3d Camera;
    cout << "Ingrese la posicion de la camera" << endl;
    //cin >> Camera.x;
    //cin >> Camera.y;
    //cin >> Camera.z;
    Camera.x = 2;Camera.y =2;Camera.z =2;
    vector<Point> vecPoints;
    for(int i = 0; i < 8; i++){
        I[i] = restarPto(Camera,I[i]);
        vecPoints.push_back(Point(floor(((I[i].x)/I[i].z)*3),floor((I[i].y/I[i].z)*3)));
        //    vecPoints[i].print();
    }
    size_t const half_size = vecPoints.size() / 2;
    vector<Point> split_lo(vecPoints.begin(), vecPoints.begin(  ) + half_size);
    vector<Point> split_hi(vecPoints.begin() + half_size, vecPoints.end());
    /*for(int i =0 ; i< 4; i++){
        split_lo[i].print();
    }
    for(int i =0 ; i< 4; i++){
        split_hi[i].print();
    }*/
    //Square sA(vecPoints[0],vecPoints[1],vecPoints[2],vecPoints[3]);
    //Square sB(vecPoints[4],vecPoints[5],vecPoints[6],vecPoints[7]);


    Square sA(Point(3,3),Point(5,3),Point(3,5),Point(5,5));
    Square sB(Point(1,1),Point(3,1),Point(1,3),Point(3,3));
    //sA.setPoints(split_lo);
    //sB.setPoints(split_hi);
    sA.printPoints();
    sB.printPoints();
    //Square sA()
    Cubo cube(sA,sB);
    /*cube.print();
    cube.movex(1);
    cube.movey(1);
    cube.print();
    cube.movex(-1);
    cube.movey(-1);
    cube.print();*/
    cube.routine();
    //GetLinesSquares(sA,sB);
}
int main() {
   
    setView();
    //Cubo()
    return 0;
}
