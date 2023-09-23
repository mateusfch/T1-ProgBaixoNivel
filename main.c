#include <stdio.h>
#include "lib_ppm.h"

int main()
{
    Img data;
    Img *image = &data;
    int i, j, r;

    Img dataH;
    Img *imageH = &dataH;
    int rh;


    rh = read_ppm("SmallImage.ppm", imageH);
    r = read_ppm("BigImage.ppm", image);

    short int larguraImgMenor = imageH->width;
    //101010101010
    short int alturaImgMenor = imageH->height;

    int larguraImgMaior = image->width;
    // 2 PIXELS DA GRANDE PARA ARMAZENAR A  LARGURA DA PEQUENA
    image->pix[0 * image->width + 0].r = (image->pix[0 * image->width + 0].r & 0b11111100) | (larguraImgMenor >> 10);
    image->pix[0 * image->width + 0].g = (image->pix[0 * image->width + 0].g & 0b11111100) | ((larguraImgMenor >> 8) & 0b00000011);
    image->pix[0 * image->width + 0].b = (image->pix[0 * image->width + 0].b & 0b11111100) | ((larguraImgMenor >> 6) & 0b00000011);

    image->pix[0 * image->width + 1].r = (image->pix[0 * image->width + 1].r & 0b11111100) | ((larguraImgMenor >> 4) & 0b00000011);
    image->pix[0 * image->width + 1].g = (image->pix[0 * image->width + 1].g & 0b11111100) | ((larguraImgMenor >> 2) & 0b00000011);
    image->pix[0 * image->width + 1].b = (image->pix[0 * image->width + 1].b & 0b11111100) | (larguraImgMenor & 0b00000011);

    // 2 PIXELS DA GRANDE PARA ARMAZENAR A ALTURA DA PQUENA
    image->pix[0 * image->width + 2].r = (image->pix[0 * image->width + 0].r & 0b11111100) | (alturaImgMenor >> 10);
    image->pix[0 * image->width + 2].g = (image->pix[0 * image->width + 0].g & 0b11111100) | ((alturaImgMenor >> 8) & 0b00000011);
    image->pix[0 * image->width + 2].b = (image->pix[0 * image->width + 0].b & 0b11111100) | ((alturaImgMenor >> 6) & 0b00000011);

    image->pix[0 * image->width + 3].r = (image->pix[0 * image->width + 1].r & 0b11111100) | ((alturaImgMenor >> 4) & 0b00000011);
    image->pix[0 * image->width + 3].g = (image->pix[0 * image->width + 1].g & 0b11111100) | ((alturaImgMenor >> 2) & 0b00000011);
    image->pix[0 * image->width + 3].b = (image->pix[0 * image->width + 1].b & 0b11111100) | (alturaImgMenor & 0b00000011);


    
    // image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixel2;      
    // image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixel2; 
        


    int altura = 0;
    int largura = 4;
    if(r==0 && rh==0){
        for(j=0; j<imageH->height; j++){


            for(i=0; i<imageH->width; i++){
                
                // MASCARAS PARA PRIMEIRO PIXEL DA IMAGEM GRANDE (passo a passo)
                unsigned int mascaraRPixelI = (imageH->pix[j * imageH->width + i].r >> 6) & 0b00000011;
                unsigned int mascaraGPixelI = (imageH->pix[j * imageH->width + i].r >> 4) & 0b00000011;
                unsigned int mascaraBPixelI = (imageH->pix[j * imageH->width + i].r >> 2) & 0b00000011;
                // MASCARAS PARA SEGUNDO PIXEL DA IMAGEM GRANDE
                unsigned int mascaraRPixel2 = imageH->pix[j * imageH->width + i].r & 0b00000011;
                unsigned int mascaraGPixel2 = (imageH->pix[j * imageH->width + i].g >> 6) & 0b00000011;
                unsigned int mascaraBPixel2 = (imageH->pix[j * imageH->width + i].g >> 4) & 0b00000011;
                // MASCARAS PARA TERCEIRO PIXEL DA IMAGEM GRANDE
                unsigned int mascaraRPixel3 = (imageH->pix[j * imageH->width + i].g >> 2) & 0b00000011;
                unsigned int mascaraGPixel3 = imageH->pix[j * imageH->width + i].g & 0b00000011;
                unsigned int mascaraBPixel3 = (imageH->pix[j * imageH->width + i].b >> 6) & 0b00000011;
                // MASCARAS PARA QUARTO PIXEL DA IMAGEM GRANDE
                unsigned int mascaraRPixel4 = (imageH->pix[j * imageH->width + i].b >> 4) & 0b00000011;
                unsigned int mascaraGPixel4 = (imageH->pix[j * imageH->width + i].b >> 2) & 0b00000011;
                unsigned int mascaraBPixel4 = imageH->pix[j * imageH->width + i].b & 0b00000011;
                
                
                int count = 0;

                while(count<4){
                    // verificar se não ultrapassa a largura da imagem maior, verificar se a altura passar tbm? ver dps, em vez de 1200 tem que deixar generico, como saber o tamanho da largura ??
                    if(largura>larguraImgMaior-4){
                        largura = 0;
                        altura++;
                    }
                    //precisa aplicar uma mascara no canal da maior tbm. zerado os 2 bits menos significativos da img maior
                    if(count == 0){ //count == 0 to no primeiro pixel dos quatro da imagem maior
                        image->pix[altura * image->width + largura].r = image->pix[altura * image->width + largura].r & 0b11111100;
                        //agora faz um or pra setar os 2 bits da img menor
                        image->pix[altura * image->width + largura].r = image->pix[altura * image->width + largura].r | mascaraRPixelI;
                        //canal green
                        image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixelI;      
                        //canal red
                        image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixelI; 
                    }
                    if(count == 1){ // pixel 2/4 da img maior
                        image->pix[altura * image->width + largura].r = (image->pix[altura * image->width + largura].r & 0b11111100) | mascaraRPixel2 ;
                        image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixel2;      
                        image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixel2; 
                    }
                    
                    if(count == 2){ // pixel 3/4 da img maior
                        image->pix[altura * image->width + largura].r = (image->pix[altura * image->width + largura].r & 0b11111100) | mascaraRPixel3;
                        image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixel3;      
                        image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixel3; 
                    }        
                    

                    if(count == 3){ // pixel 4/4 da img maior
                        image->pix[altura * image->width + largura].r = (image->pix[altura * image->width + largura].r & 0b11111100) | mascaraRPixel4;
                        image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixel4;      
                        image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixel4; 
                    }     

                    count++;
                    largura++;

                }
                
            }
            write_ppm("novas.ppm", image);
            free_ppm(image);
        }
    }


   
    char bitsImgDecodificada [imageH->width * imageH->height * 3];
        // 2 primeiros pra largura
    int larguraNova, alturaNova;
    int countDecodifica = 0;
    for(j=0; j<imageH->height*4; j++){
        for(i=0; i<imageH->width*4; i++){
            if(j==0 && i==0){
                larguraNova = image->pix[j * image->width + i].r & 0b00000011;
                larguraNova += image->pix[j * image->width + i].g & 0b00000011;
                larguraNova += image->pix[j * image->width + i].b & 0b00000011;
            }
            
            else if (j==0 && i==1)
            {
                larguraNova += image->pix[j * image->width + i].r & 0b00000011;
                larguraNova += image->pix[j * image->width + i].g & 0b00000011; 
                larguraNova += image->pix[j * image->width + i].b & 0b00000011;
            }
            else if(j==0 && i==2){
                alturaNova = image->pix[j * image->width + i].r & 0b00000011;
                alturaNova += image->pix[j * image->width + i].g & 0b00000011;
                alturaNova += image->pix[j * image->width + i].b & 0b00000011;
            }
            
            else if (j==0 && i==3)
            {
                alturaNova += image->pix[j * image->width + i].r & 0b00000011;
                alturaNova += image->pix[j * image->width + i].g & 0b00000011;
                alturaNova += image->pix[j * image->width + i].b & 0b00000011;
            }


            else{
                valor1Bit red, green, blue, red2, green2, blue2;
                
                red.valor = image->pix[j * image->width + i].r & 0b00000010;
                red2.valor = image->pix[j * image->width + i].r & 0b00000001;                
                bitsImgDecodificada[countDecodifica] = red.valor;
                bitsImgDecodificada[countDecodifica+1] = red2.valor;

                green.valor = image->pix[j * image->width + i].g & 0b00000010;
                green2.valor = image->pix[j * image->width + i].g & 0b00000001;                
                bitsImgDecodificada[countDecodifica+2] = green.valor;
                bitsImgDecodificada[countDecodifica+3] = green2.valor;

                blue.valor = image->pix[j * image->width + i].b & 0b00000010;
                blue2.valor = image->pix[j * image->width + i].b & 0b00000001;                
                bitsImgDecodificada[countDecodifica+4] = blue.valor;
                bitsImgDecodificada[countDecodifica+5] = blue2.valor;

                countDecodifica = countDecodifica+6;
            }

        }
    }
    //laço agora para formar a imagem escondida a partir de seus bits
    
    Img dataDecodificada;
    Img *imageDecodificada = &dataDecodificada;
    dataDecodificada.width = imageH->width;
    dataDecodificada.height = imageH->height;
    //imageDecodificada->pix = (Pixel *)malloc(sizeof(Pixel) * imageH->width * imageH->height);

    Pixel pixelImgDecodificada;
    int count = 0;
    
    unsigned char resultado = 0;
    unsigned char bitPego;
    int posicao = 0;
    for(i=0; i<sizeof(bitsImgDecodificada); i++){
        if(count<8){
            bitPego = bitsImgDecodificada[i];
            resultado = (resultado<<1) | bitPego;
            if(count == 7){
                pixelImgDecodificada.r = resultado;
                resultado = 0;
            }
        
        }
        else if(count<16){
            bitPego = bitsImgDecodificada[i];
            resultado = (resultado<<1) | bitPego;
            if(count == 15){
                pixelImgDecodificada.g = resultado;
                resultado = 0;
            }
        }
        
        else{
            bitPego = bitsImgDecodificada[i];
            resultado = (resultado<<1) | bitPego;
            if(count == 23){
                pixelImgDecodificada.b = resultado;
                imageDecodificada->pix[posicao] = pixelImgDecodificada;
                posicao++;
                resultado = 0;


            }
        }
        count++;
        if(count == 24){
            count = 0;
        }
    
    }
    write_ppm("pf.ppm", imageDecodificada);
    free_ppm(imageDecodificada);

    printf("OIEEEEEEEE\n");







    return 0;
}



























    // if (r == 0)
    // {
    //     printf("width: %d, height: %d\n", image->width, image->height);
    //     for (j = 0; j < image->height; j++)
    //     {
    //         /*
    //         for (i = 0; i < image->width; i++)
    //         {
    //             printf("(%d %d) %02x %02x %02x\n", i, j,
    //                    image->pix[j * image->width + i].r,
    //                    image->pix[j * image->width + i].g,
    //                    image->pix[j * image->width + i].b);
    //         }*/
    //     }

    //     // image->pix[50 * image->width + 20].r = 255;
    //     // image->pix[50 * image->width + 20].g = 255;
    //     // image->pix[50 * image->width + 20].b = 255;

    //     write_ppm("lena_copy.ppm", image);

    //     free_ppm(image);
    // }

    // r = new_ppm(image, 675, 428);

    // if (r == 0)
    // {
    //     image->pix[100 * image->width + 125].r = 255;
    //     image->pix[27 * image->width + 440].g = 255;

    //     image->pix[371 * image->width + 10].r = 192;
    //     image->pix[371 * image->width + 10].g = 192;
    //     image->pix[371 * image->width + 10].b = 192;

    //     write_ppm("test.ppm", image);
    //     free_ppm(image);
    // }


// int first = image->pix[j * image->width + i].r & 0b00000011;
// int second = image->pix[j * image->width + i].g & 0b00000011;
 // int third = image->pix[j * image->width + i].b & 0b00000011;

// int result = (second << 8) | third;
// result = (first << 16) | result; 
            
                
//imageDecodificada->pix[i-4] = result;