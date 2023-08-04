#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Livro
{
public:
    string titulo;
    string autor;
    string editora;
    int edicao;
};

void separadorline()
{
    cout << "--------------------------------" << endl;
}

void separador()
{
    cout << "--------------------------------" << endl;
    cout << endl;
}

void escreverLivroNoArquivo(string titulo, string autor, string editora, int edicao, string arquivo)
{
    fstream f(arquivo, ios::app);
    f << titulo << "," << autor << "," << editora << "," << edicao << endl;
    f.close();
}

void lerLivrosDoArquivo(string arquivo)
{

    ifstream f(arquivo);
    if (f)
    {
        string linha;
        while (getline(f, linha))
        {
            /* cout << linha << endl; */
            cout << endl;
            cout << "Título: " << linha.substr(0, linha.find(",")) << endl;                                                             // pega a linha do inicio ate a primeira virgula
            cout << "Autor: " << linha.substr(linha.find(",") + 1, linha.find(",", linha.find(",") + 1) - linha.find(",") - 1) << endl; // pega a linha da primeira virgula ate a segunda virgula
            cout << "Editora: " << linha.substr(linha.find(",", linha.find(",") + 1) + 1, linha.find(",", linha.find(",", linha.find(",") + 1) + 1) - linha.find(",", linha.find(",") + 1) - 1) << endl;
            cout << "Edição: " << linha.substr(linha.find(",", linha.find(",", linha.find(",") + 1) + 1) + 1, linha.size() - linha.find(",", linha.find(",", linha.find(",") + 1) + 1) - 1) << endl;
            cout << endl;
            separador();
        }
        f.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo: " << arquivo << endl;
    }
}

void pesquisarLivroDoArquivo(string titulo, string arquivo)
{
    ifstream f(arquivo);
    if (f)
    {
        string linha;
        bool encontrado = false;
        separadorline();

        while (getline(f, linha)) // Enquanto houver linhas no arquivo
        {
            string tituloLinha = linha.substr(0, linha.find(",")); // pega a linha do inicio ate a primeira virgula
            if (tituloLinha == titulo)
            {
                cout << endl;
                cout << "Livro encontrado: " << endl;
                cout << "Título: " << linha.substr(0, linha.find(",")) << endl;                                                             // pega a linha do inicio ate a primeira virgula
                cout << "Autor: " << linha.substr(linha.find(",") + 1, linha.find(",", linha.find(",") + 1) - linha.find(",") - 1) << endl; // pega a linha da primeira virgula ate a segunda virgula
                cout << "Editora: " << linha.substr(linha.find(",", linha.find(",") + 1) + 1, linha.find(",", linha.find(",", linha.find(",") + 1) + 1) - linha.find(",", linha.find(",") + 1) - 1) << endl;
                cout << "Edição: " << linha.substr(linha.find(",", linha.find(",", linha.find(",") + 1) + 1) + 1, linha.size() - linha.find(",", linha.find(",", linha.find(",") + 1) + 1) - 1) << endl;
                cout << endl;
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "Livro não encontrado!" << endl;
        }
        f.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo: " << arquivo << endl;
    }
}

void removerLivroDoArquivo(string titulo, string arquivo)
{
    vector<string> linhas;       // Vetor de linhas do arquivo
    ifstream inputFile(arquivo); // Abre o arquivo para leitura
    if (inputFile)
    {
        bool encontrado = false;
        string linha;
        while (getline(inputFile, linha)) // Enquanto houver linhas no arquivo
        {
            string tituloLinha = linha.substr(0, linha.find(","));
            if (tituloLinha == titulo)
            {
                encontrado = true;
            }
            if (tituloLinha == titulo)

                continue;
            linhas.push_back(linha);
        }
        inputFile.close();

        ofstream outputFile(arquivo);      // Abre o arquivo para escrita
        for (const string &linha : linhas) // Percorre o vetor de linhas
            outputFile << linha << endl;   // Escreve a linha no arquivo
        outputFile.close();
        if (!encontrado)
        {
            cout << "Livro não encontrado!" << endl;
        }
        else
        {
            cout << "Livro removido com sucesso!" << endl;
        }
    }
    else
    {
        cout << "Erro ao abrir o arquivo: " << arquivo << endl;
    }
}

int main()
{
    string tituloPesquisar;
    string tituloRemover;
    Livro l;
    string nomeArquivo = "biblioteca.csv";

    if (!ifstream(nomeArquivo))
    {
        fstream f(nomeArquivo, ios::app);
        f << "Título,Autor, Editora, Edição" << endl;
        f.close();
    }

    char continuar = 'S';
    int opcao = 0;

    do
    {
        separadorline();
        cout << "MENU" << endl;
        separadorline();
        cout << "1 - Cadastrar livro" << endl;
        cout << "2 - Listar livros" << endl;
        cout << "3 - Pesquisar livros" << endl;
        cout << "4 - Remover livro" << endl;
        cout << "5 - Sair" << endl;
        separador();
        cout << "Escolha uma opção: ";

        int opcao;

        cin >> opcao;
        cin.ignore();

        switch (opcao)
        {
        case 1:
            cout << "Cadastrar livro" << endl;

            cout << "Título: ";
            getline(cin, l.titulo);
            while (l.titulo == "")
            {
                cout << "Título não pode ser vazio!" << endl;
                cout << "Título: ";
                getline(cin, l.titulo);
            }
            cout << "Autor: ";
            getline(cin, l.autor);
            cout << "Editora: ";
            getline(cin, l.editora);
            cout << "Edição (ano): ";
            cin >> l.edicao;
            cin.ignore();

            escreverLivroNoArquivo(l.titulo, l.autor, l.editora, l.edicao, nomeArquivo);
            cout << "Dados escritos no arquivo Biblioteca com sucesso!" << endl;
            separador();

            break;
        case 2:
            separadorline();
            cout << "Livros cadastrados:" << endl;
            lerLivrosDoArquivo(nomeArquivo);
            separadorline();
            cout << "Fim da listagem" << endl;
            cout << "--------------------------------" << endl;
            cout << endl;

            break;
        case 3:

            cout << "Pesquisar livros" << endl;
            cout << "Digite o título do livro: ";

            getline(cin, tituloPesquisar);
            pesquisarLivroDoArquivo(tituloPesquisar, nomeArquivo);
            break;
        case 4:
            cout << "Remover livro" << endl;
            cout << "Informe o título do livro a ser removido: ";
            getline(cin, tituloRemover);
            removerLivroDoArquivo(tituloRemover, nomeArquivo);

            break;
        case 5:
            cout << "Programa finalizado" << endl;
            cout << "--------------------------------" << endl;
            cout << endl;
            exit(1);
            break;
        default:
            cout << "Opção inválida" << endl;
            break;
        }

    } while (opcao != 5);
    separadorline();

    return 0;
}
