#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

int main(){
    printf("============ TIC TAC TOE ===========\n\n");

    // input nama
    char nama1[50];
    char nama2[50];

    Sleep(3000);
    printf("Selamat Datang di Tic Tac Toe!\n");
    printf("Pemain 1, apa username kamu? ");
    scanf("%[^\n]", nama1); getchar();
    printf("Pemain 2, apa username kamu? ");
    scanf("%[^\n]", nama2); getchar();
    printf("Memasukan data...\n\n");
    // Sleep(3000);

    char papan[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}
    };

    bool tutorial = false;
    char jawaban;
    printf("Apakah sudah tau cara bermain? (Y/N): ");
    scanf("%c", &jawaban); getchar();
    if (jawaban == 'N' || jawaban == 'n'){
        tutorial = true;
    };

    system("cls");

    // tutorial cara main
    while (tutorial){
        printf("============ TIC TAC TOE ===========\n\n");
        printf("CARA BERMAIN\n\n");
        Sleep(2000);
        printf(" 1 | 2 | 3\n");
        printf("-----------\n");
        printf(" 4 | 5 | 6\n");
        printf("-----------\n");
        printf(" 7 | 8 | 9\n\n");

        printf("Terdapat 9 kotak yang bernomor 1 hingga 9\n");
        printf("Pemain akan memilih kotak bernomor 1 - 9 dengan \'X\' untuk pemain 1 dan \'O\' untuk pemain 2\n");
        printf("Pemain pertama yang bisa menyusun \'X\' atau \'O\' dalam bentuk horizontal, vertikal, atau diagonal\n");
        printf("Maka akan dinyatakan menang.\n\n");
        
        Sleep(5000);
        char jawaban1;
        printf("Ketik \'Y\' untuk lanjut ke permainan: ");
        scanf("%c", &jawaban1); getchar();
        if (jawaban1 == 'Y' || jawaban1 == 'y'){
            tutorial = false;
        };
    };

    // game
    system("cls");
    bool gameBerjalan = true;
    int kotakTerisi = 0;
    int giliran = 1;
    int pemenang = 0;

    while (gameBerjalan && (pemenang == 0)){
        int kotak = 0;
        printf("============ TIC TAC TOE ===========\n\n");
        printf("Giliran: %s\n\n", giliran == 1 ? nama1 : nama2);
        printf(" %c | %c | %c\n", papan[0][0], papan[0][1], papan[0][2]);
        printf("-----------\n");
        printf(" %c | %c | %c\n", papan[1][0], papan[1][1], papan[1][2]);
        printf("-----------\n");
        printf(" %c | %c | %c\n\n", papan[2][0], papan[2][1], papan[2][2]);
        
        int baris = 0;
        int kolum = 0;
        do{
            printf("Kotak apa yang kamu ingin pilih %s? ", giliran == 1 ? nama1 : nama2);
            scanf("%d", &kotak); getchar();

            baris = (kotak - 1) / 3;
            kolum = (kotak - 1) % 3;

            if (kotak < 1 || kotak > 9){
                printf("Kotak melewati batasan! Pilih kotak yang lain\n\n");
            } else if (papan[baris][kolum] != ' '){
                printf("Kotak sudah terisi! Pilih kotak yang lain\n\n");
            }
        } while (kotak < 1 || kotak > 9 || papan[baris][kolum] != ' ');

        papan[baris][kolum] =  giliran == 1 ? 'X' : 'O';
        kotakTerisi++;
        
        // cek sudah ada pemenang atau belom
        // horizontal
        for (int i = 0; i < 3; i++){
            if ((papan[i][0] == papan[i][1]) && (papan[i][1] == papan[i][2]) && (papan[i][1] != ' ')){
                gameBerjalan = false;
                pemenang = giliran;
                break;
            }
        };

        // vertikal
        for (int j = 0; j < 3; j++){
            if ((papan[0][j] == papan[1][j]) && (papan[1][j] == papan[2][j]) && (papan[1][j] != ' ')){
                gameBerjalan = false;
                pemenang = giliran;
                break;
            }
        };

        // diagonal dr kiri atas ke kanan bawah atauuu dr kiri bawah ke kanan atas
        if ((papan[0][0] == papan[1][1]) && (papan[1][1] == papan[2][2]) && (papan[1][1] != ' ')){
            gameBerjalan = false;
            pemenang = giliran;
        } else if ((papan[2][0] == papan[1][1]) && (papan[1][1] == papan[0][2]) && (papan[1][1] != ' ')){
            gameBerjalan = false;
            pemenang = giliran;
        };
        
        if ((pemenang == 0) && (kotakTerisi == 9)){
            gameBerjalan = false;
        } else if ((pemenang == 0) && gameBerjalan){
            giliran = (giliran == 1 ? 2 : 1);  
        };
        system("cls");
    };

    // menentukan pemenang
    printf("============ TIC TAC TOE ===========\n\n");
    printf(" %c | %c | %c\n", papan[0][0], papan[0][1], papan[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", papan[1][0], papan[1][1], papan[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n\n", papan[2][0], papan[2][1], papan[2][2]);

    if (pemenang == 1 || pemenang == 2){
        printf("Selamat! Pemenangnya adalah %s!\n", giliran == 1 ? nama1 : nama2);
        printf("Terima kasih telah bermain\n");
    } else if (pemenang == 0){
        printf("Tidak ada pemenang, lain kali ya :)\n");
        printf("Terima kasih telah bermain\n");
    }
    return 0;
}