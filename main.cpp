#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "rubik.h"
#include <functional>
#include <chrono>
#include <thread>

#include "learn_opengl/shader_m.h"
#include "learn_opengl/camera.h"
#include "model_cube.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <map>
#include <random> 




namespace fs = std::filesystem;

using namespace std;

////////////////////////////////////////////////////////

int modoCamara = 0;
bool zoomComplete = false;


// key counter_clockwise
bool prevPState = false;


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
// settings

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera(glm::vec3(0.0f, 0.0f, 14.0f));

bool firstMouse = true;
float yaw = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;


float currentFrame = 0.0f;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame




////############## CLASS STATE //////////////////////
bool in_circular = false;
bool in_movement = false;

class VirtualRubik{
public:

    char modoRotacion;
    char modoSolucion;
    float traslationSpeed;
    int rotloop;
    int trasloop;
    string pasoslib;
    int delta;
    int iter;
    vector<string> pasos_solu;
    vector<string> mosaicMoves;
    cuboRubik* Cubo;
    Shader* ourShader;

    vector<string> arreglo;
    vector<string> desordenar;

    float theta = -5*(PI/180) ;
 

    VirtualRubik(float x, float y, float z, char centerColor){

        random_device rd;                    // Crea un generador de números aleatorios basado en hardware
        mt19937 gen(rd());                   // Inicializa el generador utilizando la semilla rd
        uniform_int_distribution<int> dis(10, 100);  // Define una distribución uniforme de enteros entre 10 y 100
        delta = dis(gen);    


        modoSolucion = 'n';
        modoRotacion = 'n';
        rotloop = 90;
        trasloop = delta;
        string pasoslib = "";
        Cubo = new cuboRubik(x,y,z,centerColor);
        iter = 0 ;
        Cubo->init();
    }

    void draw(Shader ourShader){
        Cubo->dibujar(ourShader);
    }

    void setMosaicPatron(vector<string> mosaicMoves_){
        mosaicMoves.clear();
        for(const auto& action : mosaicMoves_){
            mosaicMoves.push_back(action);
        }
    }


    // Rotations
        void rotarUp()
    {
        
        // in_movement = true;
        rotloop -= 5;
        Cubo->Up(0, 1);
        
        Cubo->theta = -5 * (PI / 180);
        if (rotloop == 0)
        {
            Cubo->Up(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }        
    }
    void rotarUpInv()
    {
        rotloop -= 5;
        
        Cubo->theta = 5 * (PI / 180);
        // in_movement = true;
        Cubo->UpI(0, -1);
        if (rotloop == 0)
        {
            Cubo->UpI(1, -1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarDown()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->Down(0, 1);
        if (rotloop == 0)
        {
            Cubo->Down(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarDownI()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->DownI(0, 1);
        if (rotloop == 0)
        {
            Cubo->DownI(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarRigth()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->Rigth(0, 1);
        if (rotloop == 0)
        {
            Cubo->Rigth(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarRigthI()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->RigthI(0, 1);
        if (rotloop == 0)
        {
            Cubo->RigthI(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarLeft()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->Left(0, 1);
        if (rotloop == 0)
        {
            Cubo->Left(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarLeftI()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->LeftI(0, 1);
        if (rotloop == 0)
        {
            Cubo->LeftI(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarFront()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->Front(0, 1);
        if (rotloop == 0)
        {
            Cubo->Front(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarFrontI()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->FrontI(0, 1);
        if (rotloop == 0)
        {
            Cubo->FrontI(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarBack()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->Back(0, 1);
        if (rotloop == 0)
        {
            Cubo->Back(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }
    void rotarBackI()
    {
        // in_movement = true;
        rotloop -= 5;
        Cubo->BackI(0, 1);
        if (rotloop == 0)
        {
            Cubo->BackI(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            // in_movement = false;
        }
    }

    void rotarMedioX()
    {
        rotloop -= 5;
        Cubo->RigthI(0, 1);
        Cubo->Left(0, 1);

        if (rotloop == 0)
        {
            Cubo->RigthI(1, 1);
            Cubo->Left(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
            in_circular = false;
        }
    }

    void rotarMedioXI()
    {
        rotloop -= 5;
        Cubo->Rigth(0, 1);
        Cubo->LeftI(0, 1);

        if (rotloop == 0)
        {
            Cubo->Rigth(1, 1);
            Cubo->LeftI(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
        }
    }

    void rotarMedioY()
    {
        rotloop -= 5;
        Cubo->theta = 5 * (PI / 180);

        Cubo->UpI(0, -1);
        Cubo->Down(0, 1);

        if (rotloop == 0)
        {
            Cubo->UpI(1, -1);
            Cubo->Down(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
        }
    }

    void rotarMedioZ()
    {
        rotloop -= 5;
        Cubo->Front(0, 1);
        Cubo->BackI(0, 1);
        if (rotloop == 0)
        {
            Cubo->Front(1, 1);
            rotloop = 90;
            modoRotacion = 'n';
        }

    }

    void detectarRotacion()
    {
        if (this->modoRotacion == 'u')
            {
                this->rotarUp();
                this->pasoslib += "U";
            }
            else if (this->modoRotacion == 'o')
            {
                this->rotarUpInv();
                this->pasoslib += "U'";
            }
            else if (this->modoRotacion == 'd')
            {
                this->rotarDown();
                this->pasoslib += "D";
            }
            else if (this->modoRotacion == 'm')
            {
                this->rotarDownI();
                this->pasoslib += "D'";
            }
            else if (this->modoRotacion == 'r')
            {
                this->rotarRigth();
                this->pasoslib += "R";
            }
            else if (this->modoRotacion == 'h')
            {
                this->rotarRigthI();
                this->pasoslib += "R'";
            }
            else if (this->modoRotacion == 'l')
            {
                this->rotarLeft();
                this->pasoslib += "L";
            }
            else if (this->modoRotacion == 'k')
            {
                this->rotarLeftI();
                this->pasoslib += "L'";
            }
            else if (this->modoRotacion == 'f')
            {
                this->rotarFront();
                this->pasoslib += "F";
            }
            else if (this->modoRotacion == 't')
            {
                this->rotarFrontI();
                this->pasoslib += "F'";
            }
            else if (this->modoRotacion == 'b')
            {
                this->rotarBack();
                this->pasoslib += "B";
            }
            else if (this->modoRotacion == 'g')
            {
                this->rotarBackI();
                this->pasoslib += "B'";
            }
    }

};

float cameraSpeed = PI*2;

glm::mat4 circular_movement(float deltaTime)
{
    static const float radius = 3.0f;
    static float angle = 0.0f;

    // Incrementar gradualmente el ángulo de la cámara
    angle += cameraSpeed * deltaTime;

    // Calcular la nueva posición de la cámara en el círculo alrededor del eje y
    float camX = sin(-angle) * radius;
    float camZ = cos(-angle) * radius;

    glm::mat4 view;

    glm::vec3 position = glm::vec3(camX, 0.0, camZ);
    glm::vec3 front = glm::vec3(0.0, 0.0, 0.0);

    view = glm::lookAt(position, front , glm::vec3(0.0, 1.0, 0.0));
    camera.Position =  position;
    camera.Front = -position;
    return view;
}



std::map<std::string, char> movs;

void initializeMap()
{
    movs["R"] = 'r';
    movs["R'"] = 'h';
    movs["L"] = 'l';
    movs["L'"] = 'k';
    movs["F"] = 'f';
    movs["F'"] = 't';
    movs["B"] = 'b';
    movs["B'"] = 'g';
    movs["U"] = 'u';
    movs["U'"] = 'o';
    movs["D"] = 'd';
    movs["D'"] = 'm';
}

vector<string> inversa(vector<string> mov){
    vector<string> ordTemp;
    for(int i = mov.size()-1; i>=0;i--){
        string tmp;
        if(mov[i] == "R"){
            tmp="R'";
        }else if(mov[i] == "R'"){
            tmp="R";
        }else if(mov[i] == "L"){
            tmp="L'";
        }else if(mov[i] == "L'"){
            tmp="L";
        }else if(mov[i] == "F"){
            tmp="F'";
        }else if(mov[i] == "F'"){
            tmp="F";
        }else if(mov[i] == "B"){
            tmp="B'";
        }else if(mov[i] == "B'"){
            tmp="B";
        }else if(mov[i] == "U"){
            tmp="U'";
        }else if(mov[i] == "U'"){
            tmp="U";
        }else if(mov[i] == "D"){
            tmp="D'";
        }else if(mov[i] == "D'"){
            tmp="D";
        }
        ordTemp.push_back(tmp);
    }
    return ordTemp;
}

int generarNumeroAleatorio(int desde, int hasta) {
    // Obtener un generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());

    // Crear una distribución uniforme en el rango deseado
    std::uniform_int_distribution<> distribucion(desde, hasta);

    // Generar y devolver el número aleatorio
    return distribucion(gen);
}


const int row = 6;
const int col = 6;

vector<VirtualRubik*> Grid(row*col);
vector<bool> animations(Grid.size(),false);


void initGrid(){
    Grid[0] = new VirtualRubik(-3, 3, 0,'W'); //0 0
    Grid[1] = new VirtualRubik(-1.5, 3, 0,'W'); //0 1
    Grid[2] = new VirtualRubik(0, 3, 0,'B'); // 0 2
    Grid[3] = new VirtualRubik(1.5, 3, 0,'B'); //0 3
    Grid[4] = new VirtualRubik(3, 3, 0,'W'); //0 4
    Grid[5] = new VirtualRubik(4.5, 3, 0,'W'); //0 5

    Grid[6] = new VirtualRubik(-3, 1.5, 0,'W'); //1 0
    Grid[7] = new VirtualRubik(-1.5, 1.5, 0,'R'); //1 1
    Grid[8] = new VirtualRubik(0, 1.5, 0,'R'); //1 2
    Grid[9] = new VirtualRubik(1.5, 1.5, 0,'R'); //1 3
    Grid[10] = new VirtualRubik(3, 1.5, 0,'R'); //1 4
    Grid[11] = new VirtualRubik(4.5, 1.5, 0,'W'); //1 5

    Grid[12] = new VirtualRubik(-3, 0, 0,'B'); //2 0
    Grid[13] = new VirtualRubik(-1.5, 0, 0,'W'); //2 1
    Grid[14] = new VirtualRubik(0, 0, 0,'W'); //2 2
    Grid[15] = new VirtualRubik(1.5, 0, 0,'W'); //2 3
    Grid[16] = new VirtualRubik(3, 0, 0,'W'); //2 4
    Grid[17] = new VirtualRubik(4.5, 0, 0,'B'); //2 5

    Grid[18] = new VirtualRubik(-3, -1.5, 0,'B'); //3 0
    Grid[19] = new VirtualRubik(-1.5, -1.5, 0,'R'); //3 1
    Grid[20] = new VirtualRubik(0, -1.5, 0,'W'); //3 2
    Grid[21] = new VirtualRubik(1.5, -1.5, 0,'W'); //3 3
    Grid[22] = new VirtualRubik(3, -1.5, 0,'R'); //3 4
    Grid[23] = new VirtualRubik(4.5, -1.5, 0,'B'); //3 5

    Grid[24] = new VirtualRubik(-3, -3, 0,'W'); //4 0
    Grid[25] = new VirtualRubik(-1.5, -3, 0,'W'); //4 1
    Grid[26] = new VirtualRubik(0, -3, 0,'B'); //4 2
    Grid[27] = new VirtualRubik(1.5, -3, 0,'B'); //4 3
    Grid[28] = new VirtualRubik(3, -3, 0,'W'); //4 4
    Grid[29] = new VirtualRubik(4.5, -3, 0,'W'); //4 5

    Grid[30] = new VirtualRubik(-3, -4.5, 0,'W'); //5 0
    Grid[31] = new VirtualRubik(-1.5, -4.5, 0,'B'); //5 1
    Grid[32] = new VirtualRubik(0, -4.5, 0,'B'); //5 2
    Grid[33] = new VirtualRubik(1.5, -4.5, 0,'B'); //5 3
    Grid[34] = new VirtualRubik(3, -4.5, 0,'B'); //5 4
    Grid[35] = new VirtualRubik(4.5, -4.5, 0,'W'); //5 5
}

vector<vector<string>> desGris;
vector<vector<string>> order;
void desordenar(){
    vector<string> moves= {"R","R'","L","L'","F","F'","B","B'","U","U'","D","D'"};
   
    for(int i = 0;i<36;i++){
         vector<string> desOrden;
         vector<string> Order;
        int pass = generarNumeroAleatorio(5,10);
        for(int j=0 ; j<pass;j++){
            int letras=generarNumeroAleatorio(0,moves.size()-1);
            desOrden.push_back(moves[letras]);
        }
        Order = inversa(desOrden);
        order.push_back(Order);
        desGris.push_back(desOrden);
        
    }
}



void initializeMosaic()
{
    vector<vector<string>> initialMoves ={{ },{ "B", "L'", "D", "L" },{ "U", "U", "L'", "D", "L", "U", "B'", "R'", "B", "R"},{ "U'", "R", "D", "R'", "B", "D'", "B", "D"},
        { "B'", "R","D'", "R'"},{ "" },{ "U","R'", "U'"},{ "D", "L'", "D'", "L", "B", "D'", "R", "D", "B", "B", "R'", "U", "R", "U'", "D", "L", "L", "U", "D'"},{ "D'", "B", "D", "R'", "U'", "R", "L'"},
        { "L", "U'", "L", "L", "B'", "U", "D'","R'", "D", "U'", "B", "B", "L"},{ "R'", "B", "R", "B", "D'", "R", "D", "B","R'", "U", "U", "R", "B'", "D", "L'","D'" },
        { "U'", "L", "U"},{ "B'", "U'", "L", "L", "U", "L'", "B'", "U", "R'", "U'"}, { "B","U", "R", "R", "U'", "R" },{"L'", "B", "L" },{"B'", "U'", "B", "U" },
        { "B", "U'", "L", "L", "U", "L'" },{ "B'", "U'", "L", "U", "B'", "U", "R'", "R'", "U'", "R"},{ "B'", "U'", "L", "L", "U", "L'", "U", "R'", "U'", "B", "R", "B'", "R'" },
        { "B", "L'", "D", "B","L", "B'", "U", "B'", "U'"},{ "B'", "R", "D", "D", "R'", "D", "B'", "U'", "D", "L", "L", "U", "D'" },{ "B'", "R", "D", "D", "R'", "D", "B", "U", "D'", "R", "R", "D", "U'"},
        { "B'", "R", "D'", "R'", "B", "B", "R", "B", "R'"},{ "B'", "U", "R", "R", "U'", "R", "U'", "L", "U"},{ "B", "B", "D'", "R", "D", "B", "L", "R'", "U", "U", "L'", "R"},
        { "L", "B", "L", "R'","U'", "R", "L'"},{ "U'", "D", "F", "L'", "R", "D", "L", "R'"},{ "U'", "D", "F", "L'", "R", "D", "L", "R'"},{ "B'", "R'", "L", "U", "L'"},
        { "B'", "D", "L", "D'", "R'", "U", "R"}, { } ,{ "B'", "D", "U'", "L", "U", "R", "B'", "R'" }, { "D", "U'"},{ "D", "U'"} , { "F'","U'","D","L","U","U","R","U'","L'"},{ }
    };

    for(int i =0;i<36;i++){
        Grid[i]->setMosaicPatron(initialMoves[i]);
        vector<string> Order;
        Order = inversa(initialMoves[i]);
        order.push_back(Order);
    }
    
}

void desMosaic(){
    for(int i=0;i<36;i++){
        Grid[i]->setMosaicPatron(desGris[i]);
    }
}

void orMosaic(){
    for(int i=0;i<36;i++){
        Grid[i]->setMosaicPatron(order[i]);
    }
}


void triggerModoRotacion(char modoRotacion_){
    for(int i=0; i<Grid.size();i++){
        Grid[i]->modoRotacion = modoRotacion_;
    }
}


glm::vec3 lightPos(1.2f, 1.5f, 1.0f);

int main()
{

    
    // cubo1.Up();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    fs::path p = fs::current_path();
    fs::path p_current; 
	p_current = p.parent_path();

    std::stringstream ss;
	ss << std::quoted( p_current.string() );
	std::string out;
	ss >> std::quoted(out);
	
    std::string vs_path , fs_path;

	vs_path = out + "\\OwnProjects\\rubik_camada\\learn_opengl\\1.colors.vs";
	fs_path = out + "\\OwnProjects\\rubik_camada\\learn_opengl\\1.colors.fs";

    Shader lightingShader(vs_path.c_str(), fs_path.c_str());

    // establish cube
    Poligono cubo;

    vector<float> vertices;

    vertices=cubo.standar();

    lightingShader.use();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    lightingShader.setMat4("projection", projection);
   
    glPointSize(10);

    initializeMap();
    initGrid();
    
    

    int init = 0;
    int end = Grid.size() - 1;
    bool TraslationReverse = true;

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()* sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {

        currentFrame = static_cast<float>(glfwGetTime());
        // std::cout << "delta: " << currentFrame   << std::endl;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /////////////////////////////////////////////////////////////////////////////

        lightingShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        glm ::mat4 view;


        view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);
         // change the light's position values over time (can be done anywhere in the render loop actually, but try to do it at least before using the light source positions)
        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = cos(glfwGetTime() / 2.0f) * 1.0f;
        // render the cube


        for(int i = 0; i < Grid.size(); i++)
        {

            VirtualRubik* cubo = Grid[i];


            // mosaic generator
            if (cubo->modoSolucion == 'I' && cubo->modoRotacion == 'n')
            {
                // in_movement = true;
                if (cubo->iter < cubo->mosaicMoves.size())
                {
                    cubo->modoRotacion = movs[ cubo->mosaicMoves[cubo->iter] ];
                    cubo->iter++;
                }
                else
                {
                    cubo->modoSolucion = 'n';
                    cubo->iter = 0;
                    animations[i] = true;
                    // in_movement = false;
                }
            }
            cubo->detectarRotacion();
        }
        
        lightingShader.setMat4("view", view);
        
       //draw cubes
        for(auto cubo :Grid){
            cubo->draw(lightingShader);
        }


        
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Adjust the sleep time as per your preference (e.g., 10 milliseconds).
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // ###### CAMERA MOVE ######
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        // position = FORWARD;
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        // position = BACKWARD;
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        // position = LEFT;
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        // position = RIGHT;
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        // camera.ProcessCircularMovement(deltaTime);
        in_circular = true;
    }

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    //Modo Rotacion

    // if(! in_movement )
    // {

        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) // up 
        {
            triggerModoRotacion('u');
        }
        else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) // up inverse
        {
            triggerModoRotacion('o');
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // down 
        {
            triggerModoRotacion('d');
        }
        else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) // down inverse
        {
            triggerModoRotacion('m');
        }
        else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // right
        {
            triggerModoRotacion('r'); 
        }
        else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) // right inverse
        {
            triggerModoRotacion('h'); 
        }
        else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) // left
        {
            triggerModoRotacion('l');

        }
        else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) // left inverse
        {
            triggerModoRotacion('k');

        }
        else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) // front 
        {
            triggerModoRotacion('f');

        }
        else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) // front inverse
        {
            triggerModoRotacion('t');

        }
        else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) // back 
        {
            triggerModoRotacion('b');

        }
        else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) // back inverse
        {
            triggerModoRotacion('g');
        }

        else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            initializeMosaic(); 
            for(int i=0; i< Grid.size(); i++){
                Grid[i]->modoSolucion= 'I';
            }
        }
        else if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
            desordenar();
            desMosaic();
            for(int i=0; i< Grid.size(); i++){
                Grid[i]->modoSolucion= 'I';
            }
            desGris.clear();

        }
        else if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
            orMosaic();
            for(int i=0; i< Grid.size(); i++){
                Grid[i]->modoSolucion= 'I';
            }
            order.clear();
        }
    // }



};

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}