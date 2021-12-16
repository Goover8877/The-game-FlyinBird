#include "quad.h"

void Quad::setFilename(const char* fname)
{
    filename = fname;
}

void Quad::init()
{

    int width, height, nrChannels;
    unsigned char* data;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (nrChannels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    if (nrChannels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    delete data;

}

void Quad::draw()
{

    preDraw();

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_TRIANGLES);

    glTexCoord2f(0.0f, 1.0f); //Наложение текстуры (x,y)
    glVertex3f(-1.0f, -1.0f, 0.0f); // Указывает вершину (x,y,z)

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);

    glEnd();

    postDraw();

}

void Quad::destroy()
{
}

bool Quad::intersection(Quad* other)
{
    return ((other->getPositionX() + other->getScaleX() > this->getPositionX() - this->getScaleX()) &&
            (other->getPositionX() - other->getScaleX() < this->getPositionX() + this->getScaleX())) &&
            ((other->getPositionY() + other->getScaleY() > this->getPositionY() - this->getScaleY()) && 
            (other->getPositionY() - other->getScaleY() < this->getPositionY() + this->getScaleY()));

}
