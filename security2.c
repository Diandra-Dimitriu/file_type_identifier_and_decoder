#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *file_type;       
    const unsigned char *data;   
    size_t length;     
    size_t offset;          
} FileSignature;

void encription(char *input_file, char *output_file, int key)
{
    FILE *in=fopen(input_file, "rb");
    FILE *out=fopen(output_file,"wb");

    if (in==NULL || out==NULL)
    {
        perror("Error");
        exit(0);
    }

    unsigned char buffer[1024];
    size_t bytes;

    while ((bytes=fread(buffer,1,sizeof(buffer),in))>0)
    {
        for (size_t i=0;i<bytes;i++)
        {

            buffer[i]=buffer[i]+key; 
        }

        fwrite(buffer,1,bytes,out);
    }

    fclose(in);
    fclose(out);

}

void decription(char *input_file, char *output_file, int key)
{

    FILE *in=fopen(input_file, "rb");
    FILE *out=fopen(output_file,"wb");

    if (in==NULL || out==NULL)
    {
        perror("Error");
        exit(0);
    }

    unsigned char buffer[1024];
    size_t bytes;

    while ((bytes=fread(buffer,1,sizeof(buffer),in))>0)
    {
        for (size_t i=0;i<bytes;i++)
        {

            buffer[i]=buffer[i]-key;
        }

        fwrite(buffer,1,bytes,out);
    }

    fclose(in);
    fclose(out);

}

void comparey(char *input_file, char *output_file )
{
    unsigned char sig_3gp[]  = {0x66, 0x74, 0x79, 0x70, 0x33, 0x67, 0x70}; 
    unsigned char sig_avi[]  = {0x52, 0x49, 0x46, 0x46}; 
    unsigned char sig_bmp[]  = {0x42, 0x4D};
    unsigned char sig_jpg[]  = {0xFF, 0xD8, 0xFF};
    unsigned char sig_exe[]  = {0x4D, 0x5A};
    unsigned char sig_doc[]  = {0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1};
    unsigned char sig_docx[] = {0x50, 0x4B, 0x03, 0x04};
    unsigned char sig_pdf[]  = {0x25, 0x50, 0x44, 0x46, 0x2D};
    unsigned char sig_mp3[]  = {0x49, 0x44, 0x33}; 
    unsigned char sig_mp4[]  = {0x66, 0x74, 0x79, 0x70}; 
    unsigned char sig_png[]  = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    unsigned char sig_tar[]  = {0x1F, 0x8B, 0x08};

FileSignature signatures[] = {
        
        {"3GP", sig_3gp, sizeof(sig_3gp), 4},   
        {"AVI", sig_avi, sizeof(sig_avi), 0},   
        {"BMP", sig_bmp, sizeof(sig_bmp), 0},
        {"JPG", sig_jpg, sizeof(sig_jpg), 0},
        {"EXE", sig_exe, sizeof(sig_exe), 0},
        {"Legacy Office", sig_doc, sizeof(sig_doc), 0},
        {"Modern Office", sig_docx, sizeof(sig_docx), 0},
        {"PDF", sig_pdf, sizeof(sig_pdf), 0},
        {"MP3", sig_mp3, sizeof(sig_mp3), 0},
        {"MP4", sig_mp4, sizeof(sig_mp4), 4},   
        {"PNG", sig_png, sizeof(sig_png), 0},
        {"TAR.GZ", sig_tar, sizeof(sig_tar), 0}
    };

    size_t num_signatures = sizeof(signatures) / sizeof(signatures[0]);


    for (int z=0;z<=255;z++)
    {

        decription(input_file,output_file,z);

        FILE *test=fopen(output_file,"rb");
        if (test==NULL)
        {
            perror("Error");
            exit(1);
        }

        unsigned char buffer[1024];
        size_t bytes;
        int t_f=0;

        while ((bytes=fread(buffer,1,sizeof(buffer),test))>0)
        {
                for (size_t i=0; i<num_signatures;i++)
                {
                    size_t target = signatures[i].offset;
                    if (bytes >= target + signatures[i].length)
                    {
                        size_t j=0;
                        t_f=1;
                        while (j<signatures[i].length)
                        {
                            if (buffer[target+j]!=signatures[i].data[j])
                            {
                                t_f=0;
                                break;
                            }
                            j++;
                        }

                        if (j!=signatures[i].length)
                        {
                            t_f=0;
                        }

                        if (t_f==1)
                        {
                            printf("FOUND FOR %d\n",i);
                            printf("Decryption key is: %d\n", z);
                        }


                    }

            }

        }

        fclose(test);


    }
    
}
 


int main(int argc, char **argv)
{
    char *input_file=NULL, *output_file=NULL;
    input_file=argv[1];
    output_file=argv[2];
    comparey(input_file,output_file);
}
