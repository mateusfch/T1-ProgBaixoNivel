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

    printf("MDS");

    rh = read_ppm("british_summer.ppm", imageH);
    r = read_ppm("earth.ppm", image);

    short int larguraImgMenor = imageH->width;
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
    image->pix[0 * image->width + 2].r = (image->pix[0 * image->width + 2].r & 0b11111100) | (alturaImgMenor >> 10);
    image->pix[0 * image->width + 2].g = (image->pix[0 * image->width + 2].g & 0b11111100) | ((alturaImgMenor >> 8) & 0b00000011);
    image->pix[0 * image->width + 2].b = (image->pix[0 * image->width + 2].b & 0b11111100) | ((alturaImgMenor >> 6) & 0b00000011);

    image->pix[0 * image->width + 3].r = (image->pix[0 * image->width + 3].r & 0b11111100) | ((alturaImgMenor >> 4) & 0b00000011);
    image->pix[0 * image->width + 3].g = (image->pix[0 * image->width + 3].g & 0b11111100) | ((alturaImgMenor >> 2) & 0b00000011);
    image->pix[0 * image->width + 3].b = (image->pix[0 * image->width + 3].b & 0b11111100) | (alturaImgMenor & 0b00000011);
     
    int auxLargura = 0;


    int altura = 0;
    int largura = 4;
    int ultimaLargura = 0;
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
                    if(largura>larguraImgMaior){
                        
                        auxLargura = largura;
                        largura = 0;
                        altura++;
                    }
                    //precisa aplicar uma mascara no canal da maior tbm. zerado os 2 bits menos significativos da img maior
                    if(count == 0){ //count == 0 to no primeiro pixel dos quatro da imagem maior
                        //agora faz um or pra setar os 2 bits da img menor
                        image->pix[altura * image->width + largura].r = (image->pix[altura * image->width + largura].r & 0b11111100) | mascaraRPixelI;
                        //canal green
                        image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixelI;      
                        //canal red
                        image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixelI; 
                        largura++;
                    }
                    if(count == 1){ // pixel 2/4 da img maior
                        image->pix[altura * image->width + largura].r = (image->pix[altura * image->width + largura].r & 0b11111100) | mascaraRPixel2 ;
                        image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixel2;      
                        image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixel2; 
                        largura++;
                    }
                    
                    if(count == 2){ // pixel 3/4 da img maior
                        image->pix[altura * image->width + largura].r = (image->pix[altura * image->width + largura].r & 0b11111100) | mascaraRPixel3;
                        image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixel3;      
                        image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixel3; 
                        largura++;
                    }        
                    

                    if(count == 3){ // pixel 4/4 da img maior
                        image->pix[altura * image->width + largura].r = (image->pix[altura * image->width + largura].r & 0b11111100) | mascaraRPixel4;
                        image->pix[altura * image->width + largura].g = (image->pix[altura * image->width + largura].g & 0b11111100) | mascaraGPixel4;      
                        image->pix[altura * image->width + largura].b = (image->pix[altura * image->width + largura].b & 0b11111100) | mascaraBPixel4; 
                        largura++;
                    }     

                    count++;
                    //largura++;

                }
                ultimaLargura = largura;
            }

        }

        write_ppm("xdd.ppm", image);
        //free_ppm(imageH);

    }

    
    int countDecodifica = 0;
    int quantidadePixelsPequena = imageH->width * imageH->height;
    char bitsImgDecodificada[quantidadePixelsPequena * 3 * 4];

    j = 0;
   
    int countt = 0;
    for(i=4; countt<(imageH->width * imageH->height*4); i++){
        if(i>image->width){
            j++;
            i = 0;
        }

        bitsImgDecodificada[countDecodifica] = image->pix[j * image->width + i].r & 0b00000011;         
        bitsImgDecodificada[countDecodifica+1] = image->pix[j * image->width + i].g & 0b00000011;
        bitsImgDecodificada[countDecodifica+2] = image->pix[j * image->width + i].b & 0b00000011;
        
        countDecodifica = countDecodifica+3; 
        countt++;

    }

    char canalR = 0;
    char canalG = 0;
    char canalB = 0;

    Pixel pixelsImgDecodificada [larguraImgMenor * alturaImgMenor];
    

    int countAux = 0;
    int countVetorPixels = 0;
    

    int size = sizeof(bitsImgDecodificada);
    for(i=0; i<size; i = i + 4){
        Pixel p;

        while(countAux != 3){

            if(countAux == 0){
                canalR = ( bitsImgDecodificada[i] << 6) | ( bitsImgDecodificada[i+1] << 4) | (  bitsImgDecodificada[i+2] << 2) | ( bitsImgDecodificada[i+3]);
                p.r = canalR;
                countAux = 1;
            }

            else if(countAux == 1){
                canalG = (bitsImgDecodificada[i] << 6) | (bitsImgDecodificada[i+1] << 4) | (bitsImgDecodificada[i+2] << 2) | (bitsImgDecodificada[i+3]);
                p.g = canalG;
                countAux = 2;
            }

            else if(countAux == 2){
                canalB = (bitsImgDecodificada[i] << 6) | (bitsImgDecodificada[i+1] << 4) | (bitsImgDecodificada[i+2] << 2) | (bitsImgDecodificada[i+3]);
                p.b = canalB;
                // Formou um pixel da img pequena, com os três canais completos
                pixelsImgDecodificada[countVetorPixels] = p;
                countAux = 3;
                countVetorPixels++;
            }
        }

        countAux = 0;
    }

      
    

    // colocar r igual la em cima
   
    Img imgDecodificada;
    imgDecodificada.width = larguraImgMenor;
    imgDecodificada.height = alturaImgMenor;
    imgDecodificada.pix = pixelsImgDecodificada;
    
    Img *imgDeco = &imgDecodificada;



    // new_ppm(imgDeco, larguraImgMenor, larguraImgMaior);

    write_ppm("mm.ppm", imgDeco);

    // a = imgDecodificada;
    //new_ppm(a, larguraImgMenor, alturaImgMenor);


    printf("aaaaaaaaaa\n");







    return 0;
}






 // NA VERDADE É i=4
    // int aaa =0;
    // int countt = 0;
    // for(j=0; j<image->height; j++){


    //     // if(j == altura-1){
    //     //     auxLargura = ultimaLargura;
    //     // }
    //     for(i=4; i<image->width; i++){

    //         bitsImgDecodificada[countDecodifica] = image->pix[j * image->width + i].r & 0b00000011;         

    //         bitsImgDecodificada[countDecodifica+1] = image->pix[j * image->width + i].g & 0b00000011;
                
    //         bitsImgDecodificada[countDecodifica+2] = image->pix[j * image->width + i].b & 0b00000011;
                
    //         countDecodifica = countDecodifica+3; 
            
    //         countt++;
    //         if(countt> imageH->width * imageH->height * 4){
    //             i = image->width;
    //         }

    //         // if(countt>(larguraImgMenor * alturaImgMenor * 4)){
    //         //     break;
    //         // }
    //     }
        
    //     if(countt>imageH->width * imageH->height * 4){
    //         j = image->height;
    //     }
    //     // if(countt> (larguraImgMenor * alturaImgMenor * 4)){
    //     //         break;
    //     // }

    // }