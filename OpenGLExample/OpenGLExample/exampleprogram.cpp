#include "exampleprogram.h"

ExampleProgram::ExampleProgram() {
    tubes = new Tube[tubesCount];
    tubesFlag = new bool[tubesCount];
    clouds = new Quad[cloudsCount];
    cloudVel = new float[cloudsCount];
    for (int i = 0; i < tubesCount; i++) {
        tubesFlag[i] = false;
    }
    std::srand(std::time(nullptr));
    score = 0;
}


ExampleProgram::~ExampleProgram() {
    if (tubes) {
        delete tubes;
    }
    if (tubesFlag) {
        delete tubesFlag;
    }
    if (clouds) {
        delete clouds;
    }
    if (cloudVel) {
        delete cloudVel;
    }
}

HWND ExampleProgram::getHandle() {
    return hWnd;
}

void ExampleProgram::setHandle(HWND h) {
    hWnd = h;
}

void ExampleProgram::init()
{
    glShadeModel(GL_SMOOTH);                        // Enables Smooth Shading //Обеспечивает плавное затенение
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                   // Black Background //Черный фон
    glClearDepth(1.0f);                         // Depth Buffer Setup//Настройка буфера глубины
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing//Глубинные тестированя
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Test To Do//Тип Теста Глубины, Который Нужно Выполнить
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations//Действительно Хорошие Перспективные Расчеты

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sky.setFilename("fon.png");
    sky.init();
    sky.setScaleX(5.0f);
    sky.setScaleY(5.0f);

    bird.setFilename("ptica.png");
    bird.init();
    //quad1.setPositionX(-3.0f);
    x = -0.1f;
    bird.setScaleX(0.4f);
    bird.setScaleY(0.3f);

    //hitbox.setFilename("poi.jpg");
    //hitbox.init();
    hitbox.setScaleX(0.3f);
    hitbox.setScaleY(0.1f);

    fallingBird.setFilename("truba.jpg");
    fallingBird.init();

    fallingBird.setScaleX(0.3f);
    fallingBird.setScaleY(0.1f);
    


    fire.setFilename("ogon.jpg");
    fire.init();
    fire.setScaleX(1.0f);
    fire.setScaleY(0.1f);
    fire.setPositionY(-3.0f);
    

    tube.setTextures("truba.jpg", "truba.jpg");
    tube.init();

    tube.setGap(1.0f);
    tube.setScaleY(5.0f);
    tube.setScaleX(0.2f);
    tube.setPositionX(0.0f);
    tube.setPositionY(0.0f);

    for (int i = 0; i < tubesCount; i++) {
        tubes[i].setTextures("truba2.png", "truba.png");
        tubes[i].init();

        tubes[i].setGap(1.0f);
        tubes[i].setScaleY(5.0f);
        tubes[i].setScaleX(0.2f);
        tubes[i].setPositionX(4.0f + (float)i * 2.0f);
        float y = 1.0f - 2.0f * ((float)std::rand() / (float)RAND_MAX);
        tubes[i].setPositionY(y);

    }
    for (int i = 0; i < cloudsCount; i++) {
        clouds[i].setFilename("Oblake.png");
        clouds[i].init();
        float scale = 1.5f - ((float)std::rand() / (float)RAND_MAX);
        clouds[i].setScaleY(scale);
        clouds[i].setScaleX(scale);
        float x = 4.0f - 8.0f * ((float)std::rand() / (float)RAND_MAX);
        clouds[i].setPositionX(x);
        float y = 3.0f - 4.0f * ((float)std::rand() / (float)RAND_MAX);
        clouds[i].setPositionY(y);
        cloudVel[i]=0.02f-0.01f* ((float)std::rand() / (float)RAND_MAX);
    }

    //MessageBox(0, L"hit", L"", MB_OK);
}

void ExampleProgram::draw()
{
    // x = x0 + v * t + a * t^2 / 2
    // v = v0 + a * t;


    //y -= step;
    /*counter++;
    if (isKeyDown(VK_SPACE)) {
        //y += 5.0*step;
        if (counter > 50) {
            vy = -0.05;
            counter = 0;
        }
    }*/

    // Ek + Ep = Ek1 + Ep1
    //

    /*if (isKeyDown(VK_SPACE)) {
        //y += astep;
        // check
        //MessageBox(0, L"hello, world", L"", MB_OK);
    }
    ////////////////////////////////////////
    if (isKeyDown(VK_LEFT)) {
        x -= step;
    }
    if (isKeyDown(VK_RIGHT)) {
        x += step;
    }
    if (isKeyDown(VK_UP)) {
        y += step;
    }
    if (isKeyDown(VK_DOWN)) {
        y -= step;
    }*/

    if (game) {

       // hit = bird.intersection(&fire);

       // hit = tube.intersection(&bird);
        hit = false;
        for (int i = 0; i < tubesCount; i++) {
            hit |= tubes[i].intersection(&hitbox);
        }
        hit |= fire.intersection(&hitbox);
        // пересечение с fire

        vy = vy + 0.001;
        if (hit) {
            //vy = - 0.8f * abs(vy);
            game = false;
        }
        if (isKeyDown(VK_SPACE)) {
            vy = -0.013f;//Птица скорость поднятия
        }
        y = y - vy;

        //fire.setPositionX(fire.getPositionX() - step);
        // движение tube
        for (int i = 0; i < tubesCount; i++) {
            if (tubes[i].getPositionX() < -0.1f) {
                if (!tubesFlag[i]) {
                    score++;
                    tubesFlag[i] = true;
                }
            }
        }
        char str[256];
        sprintf_s(str, "OpenGLExample | score: %i", score);
        //OutputDebugStringA(str);

        wchar_t wstr[256];
        //size_t srcSize = strlen(str) + 1;
        size_t destSize;
        mbstowcs_s(&destSize, wstr, str, strlen(str));
        SetWindowText(getHandle(), wstr);
        
        tube.setPositionX(tube.getPositionX() - 0.015f);
        for (int i = 0; i < tubesCount; i++) {
            tubes[i].setPositionX(tubes[i].getPositionX()-0.015f);
        }
        for (int i = 0; i < cloudsCount; i++) {
            clouds[i].setPositionX(clouds[i].getPositionX() - cloudVel[i]);
        }
        
        for (int i = 0; i < tubesCount; i++) {
            if (tubes[i].getPositionX() < -5.0f) {
                tubes[i].setPositionX(5.0f);
                tubesFlag[i] = false;
                float y = 1.0f - 2.0f * ((float)std::rand() / (float)RAND_MAX);
                tubes[i].setPositionY(y);
                //MessageBox(0, L"!!!", L"", MB_OK);
            }
        }
        for (int i = 0; i < cloudsCount; i++) {
            if (clouds[i].getPositionX() < -6.0f) {
                float x = 3.0 * ((float)std::rand() / (float)RAND_MAX);
                clouds[i].setPositionX(6.0f + x);
                float y = 3.0f -4.0f * ((float)std::rand() / (float)RAND_MAX);
                clouds[i].setPositionY(y);
                cloudVel[i]=0.02f - 0.01f * ((float)std::rand() / (float)RAND_MAX);
                float scale = 1.5f - ((float)std::rand() / (float)RAND_MAX);
                clouds[i].setScaleY(scale);
                clouds[i].setScaleX(scale);
            }
        }
        // 0 2 4 6 8 10 .. 18
        // -2 0 2 4 6 ...
        // каким образом сделать игру бесконечной, чтобы трубы постоянно появлялись. что с ними сделать?

    }
    else {
        if (!gameovermessage) {
            char str[256];
            sprintf_s(str, "Game Over. Your score: %i\n", score);
            OutputDebugStringA(str);

            wchar_t wstr[256];
            //size_t srcSize = strlen(str) + 1;
            size_t destSize;
            mbstowcs_s(&destSize, wstr, str, strlen(str));
            MessageBox(getHandle(), wstr, L"", MB_OK);
        }
        gameovermessage = true;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear The Screen And The Depth Buffer//Очистите Экран И Буфер Глубины
    glLoadIdentity();                           // Reset The Current Modelview Matrix//Сброс Текущей Матрицы Представления Модели
    glTranslatef(0.0f, 0.0f, -8.0f);
    //glRotatef(angle, 0.0f, 1.0f, 0.0);
    //glScalef(2.0f, 2.0f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    
    hitbox.setPositionX(x);
    hitbox.setPositionY(y);
    bird.setPositionX(x);
    bird.setPositionY(y);
    fallingBird.setPositionX(x);
    fallingBird.setPositionY(y);
    sky.draw();
    for (int i = 0; i < cloudsCount; i++) {
        clouds[i].draw();
    }
    
    /*if (!hit) {
        bird.draw();
    }
    else {
        fallingBird.draw();
    }*/

    for (int i = 0; i < tubesCount; i++) {
        tubes[i].draw();
    }

    //hitbox.draw();
    bird.draw();

    //fire.draw();
    //tube.draw();
 
    // VK_LEFT, VK_RIGHT

   /* x += step;
    if (x > 4.0f) {
        x = -4.0f;
    }*/ 

       

}
