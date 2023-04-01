#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;


struct Point{
    Point(float x, float y)
        : x(x), y(y){}
    Point(){};
    float x;
    float y;
    void print(){
        cout << x << ", " << y << endl;
    }
  
};
struct Square{
    Square(Point PointA, Point PointB, Point PointC, Point PointD)
    :   PointA(PointA), PointB(PointB), PointC(PointC), PointD(PointD){};
    Square(){};
    Point PointA;
    Point PointB;
    Point PointC;
    Point PointD;
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
};


void ValidateLine(Point a,Point b, float grilx, float grily, vector<vector<char>> &grill){
    
    if ((((((a.y-b.y)/(a.x-b.x))*(grilx - b.x))-(grily - b.y)) >= -1) && (((((a.y-b.y)/(a.x-b.x))*(grilx - b.x))-(grily - b.y)) <= 1)){
        grill[grilx][grily] = '*';
    }

}
float gety(Point A, Point B, float itr){
    return (((A.y-B.y)/(A.x - A.y))*(itr - A.x)) + A.y; 
}
float getx(Point A, Point B, float itr){
    return A.x + ((itr - A.y)/((A.y-B.y)/(A.x-B.x)));
}
void GetLinesSquares(Square sA, Square sB){
    // aqui definimos las lineas que queremos dibujar, damos el a1->a2
    // linea arriba primer cuadrado
    sA.printPoints();
    cout << "sA" <<endl;
    sB.printPoints();
    vector<char> row;
    row.assign(100,' ');
    // get y es la que me da y despues de darle un x, calulando la formula desde su funcion.
    vector<vector<char>> grill;
    grill.assign(100,row);

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
    /*
    */

    /*
    */
    for(int ii = 0; ii < 100; ii++){
        for(int jj = 0; jj < 100; jj++){
            cout << grill[ii][jj] << '\t';
        }
        cout << endl;
    }

    
}
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
    cin >> Camera.x;
    cin >> Camera.y;
    cin >> Camera.z;
    //Camera.x = 2;Camera.y =3;Camera.z =5;
    vector<Point> vecPoints;
    for(int i = 0; i < 8; i++){
        I[i] = restarPto(Camera,I[i]);
        vecPoints.push_back(Point(floor(((I[i].x)/I[i].z)*20),floor((I[i].y/I[i].z)*20)));
        //    vecPoints[i].print();
    }
    size_t const half_size = vecPoints.size() / 2;
    vector<Point> split_lo(vecPoints.begin(), vecPoints.begin(  ) + half_size);
    vector<Point> split_hi(vecPoints.begin() + half_size, vecPoints.end());
    cout << "dividides: " << endl;
    /*for(int i =0 ; i< 4; i++){
        split_lo[i].print();
    }
    for(int i =0 ; i< 4; i++){
        split_hi[i].print();
    }*/
     Square sA(vecPoints[0],vecPoints[1],vecPoints[2],vecPoints[3]);
    Square sB(vecPoints[4],vecPoints[5],vecPoints[6],vecPoints[7]);
    //sA.setPoints(split_lo);
    //sB.setPoints(split_hi);
    //sA.printPoints();
    GetLinesSquares(sA,sB);
}
int main() {
   
    
    setView();
    return 0;
}
