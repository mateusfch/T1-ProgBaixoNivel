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


    printf("oo");
    
    rh = read_ppm("british_summer.ppm", imageH);
    r = read_ppm("earth.ppm", image);
    int altura = 0;
    int largura = 0;
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
                    if(largura>1200){
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
            write_ppm("acopy.ppm", image);
            free_ppm(image);
        }
    }

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
