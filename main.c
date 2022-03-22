#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Hungarian.h"
#define MAX_LINE 1024

void deletechar(char a[],char c)
{
    int i,j;
    for(i=0,j=0; *(a+i)!='\0'; i++)
    {
        if(*(a+i)==c)
            continue;
        else
        {
            *(a+j)=*(a+i);
            j++;
        }
    }
    *(a+j)='\0';
}


int main()
{
    char buf[MAX_LINE];  /*缓冲区*/
    FILE *fp;            /*文件指针*/
    int len;             /*行字符个数*/
    if((fp = fopen("test.txt","r")) == NULL)
    {
    perror("fail to read");
    exit (1) ;
    }
    
    model_box_data.number = 0;
    track_box_data.number = 0;
    sort.iou_threshold = 0.3;


    
    while(fgets(buf,MAX_LINE,fp) != NULL)
    {
        len = strlen(buf);
        int a,b;
        float c,d,e,f,g;

        buf[len-1] = '\0';  /*去掉换行符*/
        deletechar(buf,',');
        sscanf(buf, "%d %d %f %f %f %f %f", &a, &b, &c, &d, &e, &f, &g);
        // printf("%d %f %f %f %f  \n",a, c, d, e, f);

        // 初始化车位框；
        if (a == 42)
        {
            // init_cardata(&model_box_data,model_box, c, d, e, f);
            float mx1,my1,mw,mh;
            mx1 = c;
            my1 = d;
            mw = e;
            mh = f;
            model_box.x1 = mx1;
            model_box.y1 = my1;
            model_box.x2 = mx1 + mw;
            model_box.y2 = my1 + mh;
            model_box.x = mx1 + mw / 2;
            model_box.y = my1 + mh / 2;
            model_box.h = mh;
            model_box.w = mw;
            getdata(&model_box_data,model_box);
        }
        else if (a == 43)
        {
            // init_cardata(&track_box_data,track_box, c, d, e, f);
            float mx1,my1,mw,mh;
            mx1 = c;
            my1 = d;
            mw = e;
            mh = f;
            track_box.x1 = mx1;
            track_box.y1 = my1;
            track_box.x2 = mx1 + mw;
            track_box.y2 = my1 + mh;
            track_box.x = mx1 + mw / 2;
            track_box.y = my1 + mh / 2;
            track_box.h = mh;
            track_box.w = mw;
            getdata(&track_box_data,track_box);
        }
        else{continue;}
    }


    Hungarian(&model_box_data, &track_box_data, &iou_data, &data_hungarian, &Output, &outforsort,&hungary,&sort);

    return 0;
}


