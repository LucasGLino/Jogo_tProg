#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

namespace Gerenciadores{
    class GerenciadorGrafico{
        private:
            RenderWindow* window;
            View view;
            static unsigned int largura;
            static unsigned int altura; 

            static GerenciadorGrafico* pInstancia;

            GerenciadorGrafico();

        public:
            ~GerenciadorGrafico();

            static GerenciadorGrafico* getInstancia();

            void desenhar(Sprite* corpo);

            void desenhar(RectangleShape aux);

            void desenhar(Text* texto);

            RenderWindow* getWindow()const;

            void limpar();

            bool isOpen()const;

            void centralizar(Vector2f pos);

            View getView() const;

            unsigned int getLargura(){return largura;}

            unsigned int getAltura(){return altura;}

            void mostrar();

            void fechar();
    };
}
