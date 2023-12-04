#include <iostream>
#include <vector>


using namespace std;

class Poligono{
public:

    vector<vector<float>> vertices;
    vector<vector<float>> vecColor;

    Poligono()
    {
        cube();
    }
    
    void cube(){
        vertices={
            //frontal
            {-0.5f,  0.5f,  0.5f,1},
            { 0.5f,  0.5f,  0.5f,1},
            {-0.5f, -0.5f,  0.5f,1},
            { 0.5f,  0.5f,  0.5f,1},
            {0.5f, -0.5f,  0.5f,1},
            {-0.5f, -0.5f,  0.5f,1},
            //Trasera
            {-0.5f,  0.5f, -0.5f,1},
            { 0.5f,  0.5f, -0.5f,1},
            {-0.5f, -0.5f, -0.5f,1},
            {-0.5f, -0.5f, -0.5f,1},
            {0.5f,  0.5f, -0.5f,1},
            {0.5f, -0.5f, -0.5f,1},
            //Superior
            {-0.5f,  0.5f,  0.5f,1},
            {0.5f,  0.5f,  0.5f,1},
            {0.5f,  0.5f, -0.5f,1},
            {-0.5f,  0.5f,  0.5f,1},
            {0.5f,  0.5f, -0.5f,1},
            {-0.5f,  0.5f, -0.5f,1},
            //Inferior
            {-0.5f, -0.5f,  0.5f,1},
            {0.5f, -0.5f,  0.5f,1},
            {0.5f, -0.5f, -0.5f,1},
            {-0.5f, -0.5f,  0.5f,1},
            {0.5f, -0.5f, -0.5f,1}, 
            {-0.5f, -0.5f, -0.5f,1},
            //Derecha
            {0.5f, -0.5f,  0.5f,1}, 
            {0.5f, -0.5f, -0.5f,1}, 
            {0.5f,  0.5f, -0.5f,1}, 
            {0.5f, -0.5f,  0.5f,1}, 
            {0.5f,  0.5f, -0.5f,1}, 
            {0.5f,  0.5f,  0.5f,1}, 
            //Izquierda        
            {-0.5f, -0.5f,  0.5f,1}, 
            {-0.5f, -0.5f, -0.5f,1},
            {-0.5f,  0.5f, -0.5f,1},
            {-0.5f, -0.5f,  0.5f,1},
            {-0.5f,  0.5f, -0.5f,1},
            {-0.5f,  0.5f,  0.5f,1}
           
        };
        
        vecColor={
            {Color("verde")},
            {Color("azul")},
            {Color("amarillo")},
            {Color("blanco")},
            {Color("naranja")},
            {Color("rojo")},
        };

    }

    vector<float> Color(string col){
        
        vector<float> Color;
        if (col == "verde") Color={0.0f, 1.0f, 0.0f};
        else if (col == "rojo") Color={1.0f, 0.0f, 0.0f};
        else if (col == "amarillo") Color={1.0f, 1.0f, 0.0f};
        else if (col == "blanco") Color={1.0f, 1.0f, 1.0f};
        else if (col == "azul") Color={0.0f, 0.0f, 1.0f};
        else if (col == "naranja") Color={1.0f, 0.5f, 0.0f};
        return Color;
    }

   void imprimirVectorFloat(const std::vector<float>& vec) {
    for (const float& elemento : vec) {
        std::cout << elemento << ",";
    }
    std::cout << std::endl;
    }

    vector<float> standar(){
        vector<float> temp={};
        vector<vector<float>> tempV=vertices;
        int col=0;
        int flag=1;
        
        for (int i =0;i<vertices.size();i++){
            tempV[i].resize(3);
            tempV[i].insert(tempV[i].end(),vecColor[col].begin(), vecColor[col].end());
            if((i+1) % 6==0) col++;
        }

        for (int i=0;i<vertices.size();i++,flag++){
            temp.insert(temp.end(),tempV[i].begin(), tempV[i].end());           
        }
        
        return temp;
    }
};
