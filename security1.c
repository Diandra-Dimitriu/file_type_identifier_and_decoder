#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void decription(char *input_file, char *output_file,int key)
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

int main(int argc, char **argv)
{
    int out=0, e=0,d=0,key=0;
    char *input_file=NULL, *output_file=NULL;
    for (int i=1;i<argc;i++)
    {
        if (strcmp(argv[i],"-e")==0)
        {
            e=1;
        }
        else if (strcmp(argv[i],"-d")==0)
        {
            d=1;
        }
        else if (strcmp(argv[i],"-o")==0 && out==0)
        {
            if (i+1<argc)
            {
                output_file= argv[i+1];
                out=1;
                i++;
            }
            else
            {
                perror("No output file given");
                return 1;
            }
        }
        else if (strcmp(argv[i],"-k")==0)
        {
            if (i+1<argc)
            {
                key= atoi(argv[i+1]);
                i++;
            }
            else
            {
                perror("No key given");
                return 1;
            }
        }
        else
        {
            input_file = argv[i];
        }
    }



    if (e==1 && out==1)
    {
        encription(input_file,output_file,key);
    }
    else if (d==1 && out==1)
    {
        decription(input_file,output_file,key);
    }
    else 
    {
        perror("Argument input wrong");
        return 1;
    }
}