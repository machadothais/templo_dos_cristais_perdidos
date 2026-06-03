#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int jogarNovamente = 1, rodada = 0, escolha = 0, palpite = 0, numeroPortal = 0, evento = 0, energia = 0, cristais = 0,
    chaves = 0, risco = 0, ganho = 0, perda = 0, dadoJogador = 0, dadoGuardiao = 0, totalRodadas = 8;

    /*
        Trabalho - Modulo 3
        Jogo: Templo dos Cristais Perdidos

        Regras atendidas:
        - Usa estruturas sequenciais, condicionais, for e while.
        - Usa randomizacao com srand(time(NULL)) e rand().
        - Nao usa vetores, matrizes, funcoes proprias ou procedimentos.
        - Possui interacao com o usuario.
    */

    srand(time(NULL)); /* Equivalente ao randomize: inicia a geracao aleatoria. */

    printf("============================================\n");
    printf("        TEMPLO DOS CRISTAIS PERDIDOS        \n");
    printf("============================================\n");
    printf("Objetivo: reunir 35 cristais antes do fim da expedicao.\n");
    printf("Voce tera 8 rodadas, energia limitada e eventos aleatorios.\n");
    printf("Cuidado: descansar ajuda, mas aumenta o risco do templo.\n\n");

    while (jogarNovamente == 1) {
        energia = 25;
        cristais = 0;
        chaves = 0;
        risco = 0;

        printf("\nNova expedicao iniciada!\n");
        printf("Energia inicial: %d | Cristais: %d | Chaves: %d\n", energia, cristais, chaves);

        for (rodada = 1; rodada <= totalRodadas && energia > 0 && cristais < 35; rodada++) {
            printf("\n--------------------------------------------\n");
            printf("Rodada %d de %d\n", rodada, totalRodadas);
            printf("Status -> Energia: %d | Cristais: %d | Chaves: %d | Risco: %d\n", energia, cristais, chaves, risco);
            printf("Escolha sua acao:\n");
            printf("1 - Explorar uma sala do templo\n");
            printf("2 - Descansar perto da fogueira\n");
            printf("3 - Tentar abrir um portal secreto\n");

            escolha = 0;
            while (escolha < 1 || escolha > 3) {
                printf("Digite sua escolha: ");
                scanf("%d", &escolha);

                if (escolha < 1 || escolha > 3) {
                    printf("Opcao invalida. Escolha 1, 2 ou 3.\n");
                }
            }

            if (escolha == 1) {
                printf("\nVoce entrou em uma sala escura do templo...\n");
                energia = energia - 3;
                evento = rand() % 100 + 1;

                if (evento <= 35) {
                    ganho = rand() % 8 + 4;
                    cristais = cristais + ganho;
                    printf("Boa! Voce encontrou %d cristais brilhantes.\n", ganho);
                } else if (evento <= 60) {
                    numeroPortal = rand() % 5 + 1;
                    printf("Um enigma apareceu na parede.\n");
                    printf("Tente adivinhar o numero magico do portal, de 1 a 5: ");
                    scanf("%d", &palpite);

                    if (palpite == numeroPortal) {
                        cristais = cristais + 8;
                        chaves = chaves + 1;
                        printf("Acertou! Voce ganhou 8 cristais e 1 chave antiga.\n");
                    } else {
                        energia = energia - 4;
                        printf("Errou! O numero era %d. Voce perdeu 4 de energia.\n", numeroPortal);
                    }
                } else if (evento <= 80) {
                    perda = rand() % 5 + 2;
                    energia = energia - perda;
                    risco = risco + 1;
                    printf("Armadilha ativada! Voce perdeu %d de energia.\n", perda);
                } else {
                    chaves = chaves + 1;
                    risco = risco + 1;
                    printf("Voce encontrou uma chave antiga, mas o templo ficou mais instavel.\n");
                }
            } else if (escolha == 2) {
                ganho = rand() % 7 + 4;
                energia = energia + ganho;
                risco = risco + 2;

                if (energia > 30) {
                    energia = 30;
                }

                printf("\nVoce descansou e recuperou energia. Energia atual: %d.\n", energia);
                printf("Porem, o tempo parado aumentou o risco do templo.\n");

                evento = rand() % 100 + 1;
                if (evento <= 40 && cristais > 0) {
                    perda = rand() % 5 + 1;

                    if (perda > cristais) {
                        perda = cristais;
                    }

                    cristais = cristais - perda;
                    printf("Um pequeno guardiao roubou %d cristais enquanto voce descansava!\n", perda);
                } else {
                    printf("Nada de ruim aconteceu durante o descanso.\n");
                }
            } else {
                printf("\nVoce tentou abrir um portal secreto.\n");
                energia = energia - 2;

                if (chaves > 0) {
                    chaves = chaves - 1;
                    dadoJogador = rand() % 6 + 1;
                    dadoGuardiao = rand() % 6 + 1;

                    printf("Voce usou uma chave antiga.\n");
                    printf("Seu poder: %d | Poder do guardiao: %d\n", dadoJogador, dadoGuardiao);

                    if (dadoJogador + 1 >= dadoGuardiao) {
                        cristais = cristais + 10;
                        risco = 0;
                        printf("Portal dominado! Voce ganhou 10 cristais e reduziu o risco para 0.\n");
                    } else {
                        energia = energia - 5;
                        risco = risco + 2;
                        printf("O guardiao venceu! Voce perdeu 5 de energia e o risco aumentou.\n");
                    }
                } else {
                    dadoJogador = rand() % 6 + 1;
                    dadoGuardiao = rand() % 6 + 1;

                    printf("Voce nao tinha chave, entao tentou forcar o portal.\n");
                    printf("Seu poder: %d | Poder do guardiao: %d\n", dadoJogador, dadoGuardiao);

                    if (dadoJogador > dadoGuardiao) {
                        cristais = cristais + 6;
                        printf("Voce teve sorte e conseguiu 6 cristais!\n");
                    } else {
                        energia = energia - 6;
                        risco = risco + 2;
                        printf("O portal reagiu! Voce perdeu 6 de energia.\n");
                    }
                }
            }

            if (risco >= 6 && energia > 0) {
                printf("\nALERTA: o templo entrou em colapso parcial!\n");
                energia = energia - 4;
                risco = 2;
                printf("Voce perdeu 4 de energia, mas o risco voltou para 2.\n");
            }

            if (energia < 0) {
                energia = 0;
            }
        }

        printf("\n============================================\n");
        printf("Resultado final da expedicao\n");
        printf("Energia: %d | Cristais: %d | Chaves restantes: %d\n", energia, cristais, chaves);

        if (cristais >= 35 && energia > 0) {
            printf("VITORIA! Voce encontrou os Cristais Perdidos e escapou do templo.\n");
        } else if (energia <= 0) {
            printf("DERROTA! Sua energia acabou antes de sair do templo.\n");
        } else if (cristais >= 25) {
            printf("FINAL PARCIAL! Voce escapou com muitos cristais, mas nao achou o tesouro principal.\n");
        } else {
            printf("DERROTA! A expedicao terminou sem cristais suficientes.\n");
        }

        printf("============================================\n");

        jogarNovamente = 0;
        while (jogarNovamente != 1 && jogarNovamente != 2) {
            printf("\nDeseja jogar novamente? Digite 1 para sim ou 2 para nao: ");
            scanf("%d", &jogarNovamente);

            if (jogarNovamente != 1 && jogarNovamente != 2) {
                printf("Opcao invalida. Digite 1 ou 2.\n");
            }
        }
    }

    printf("\nObrigado por jogar o Templo dos Cristais Perdidos!\n");

    return 0;
}
