/*
2022-03
mai.yu
ptyhon to C 
kalman and Hungarian Algorithm
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define datasize 2518*7
#define row 2518
/*数据记录在一个txt文件内
/home/leo/workbench/AI/sort/sort-master-to/data/train/track2_1/det
  数据结构 
1, -1, 678.103821, 313.205420, 307.138653, 149.504815, 1
1, -1, 44.705419, 161.794373, 284.008173, 164.823273, 2
1, -1, 691.463135, 623.042340, 319.739260, 181.485492, 3
1, -1, 25.721938, 487.058136, 315.085832, 159.433363, 4
1, -1, 700.140394, 795.891174, 321.602893, 192.988695, 5
第一帧 无用 左上角横坐标  左上角纵坐标  目标框的宽  目标框的高  框ID
按处理的要求读取txt内的文件  17,626个数据
*/
//设定接下来算法要用到的参数
typedef struct
{
int num_frame[row],id[row],ii[row];
double x[row],y[row],w[row],h[row];
char datadir[100];
float iou_threshold;
int max_age, min_hits;
int frame_flag,frame_count;
// double matched[];
// double unmatched_dets[];
// double unmatched_trks[];
}SortObj;

typedef struct
{
  int row_mat , col_mat;   //row_mat矩阵行  col矩阵列
  double *data_mat;     //矩阵的数据
}Matrix;

SortObj sortObj;
Matrix  matrix;
void read_detection_data(SortObj *obj);
int get_number_of_frames(int size,SortObj *obj);
void sort_default_param_set(SortObj *obj);
Matrix* init_matrix(Matrix *mat,int row_m,int col_m);
void value_matrix(Matrix *mat,double *array);
void print_matrix(Matrix *mat);
int size_matrix(Matrix *mat);

int size_matrix(Matrix *mat)
{
  int ii=mat->col_mat*mat->row_mat;
  printf("%d--done!!!\n",ii);
	return ii;
  
}

void print_matrix(Matrix *mat)
{
  printf("size--%d\n",size_matrix(mat));
	for (int i=0;i<size_matrix(mat);i++)
	{
		printf("%lf\t", mat->data_mat[i]);
		if ((i+1)%mat->row_mat == 0)
			printf("\n");
	}
			
}



void value_matrix(Matrix *mat,double *array) 		//给矩阵赋值
{
	if (mat->data_mat != NULL)
	{
		memcpy(mat->data_mat, array, mat->row_mat * mat->col_mat* sizeof(double));
	}
}

Matrix* init_matrix(Matrix *mat,int row_m,int col_m)
{
   	if (row_m>0 && col_m>0)
	{
		mat = (Matrix*)malloc(sizeof(Matrix));
		mat->row_mat = row_m;
		mat->col_mat = col_m ;
		mat->data_mat = (double*)malloc(sizeof(double)*row_m*col_m);
		memset(mat->data_mat,0,sizeof(double)*row_m*col_m);
		return mat;
	}
	else 
		return NULL;


}

void sort_default_param_set(SortObj *obj)
{

    strcpy(obj->datadir,"/home/leo/workbench/AI/C-sort/det/det.txt");
    obj->max_age=1;
    obj->min_hits=3;
    obj->iou_threshold=0.3;
    obj->frame_count=0;
}

void read_detection_data(SortObj *obj)
{
  FILE *fp;
  fp=fopen(obj->datadir,"r");
  if(fp == NULL)
  {
      printf("无法打开文件！！\n");
  }
    //数据结构 1, -1, 678.103821, 313.205420, 307.138653, 149.504815, 1
   for (int i = 0; i < row; i++)
    {
        fscanf(fp, "%d, %d, %lf, %lf, %lf, %lf, %d", &(obj->num_frame[i]), &(obj->ii[i]),&(obj->x[i]),&(obj->y[i]),&(obj->w[i]),&(obj->h[i]),&(obj->id[i]));
        //printf("%d, %d, %lf, %lf, %lf, %lf, %d\n",obj->num_frame[i],obj->ii[i],obj->x[i],obj->y[i],obj->w[i],obj->h[i],obj->id[i]);
    }
  fclose(fp);
 }
  //求得数据的帧数
  int get_number_of_frames(int size,SortObj *obj)
  {
   int max = obj->num_frame[0];
	for ( int i = 0; i < size; i++)
	{
		if (max < obj->num_frame[i])
		{
			max = obj->num_frame[i];
		}
	}
	printf("max of array:%d\n",max);
    return max;
  }
  /*
  操作数据返回trackers  即使检测为空，也必须为每一帧调用一次此方法（对于未检测的帧，使用np.empty（0，5））
  返回一个类似的数组，其中最后一列是对象ID
  返回的对象数量可能与提供的检测数量不同  
  */
 
 
    //pop trackers in to_del

    //matched ,unmatched_dets,unmatched_trks 关联det和tracks
    /*
      1、传入det和trackers的数据求得iou矩阵 
      2、获取matched_indices 矩阵的行列索引 
      3、创建unmatched_detections[]   判断det中的id 是否在matched_idices中
      4、创建unmatched_trackers[]     判断tra中的id 是否在matched_idices中
      5、创建matches                  过掉低iou的
      6、返回 3


    */
    

    //matched, update


    //unmatched  kalmanBoxTracker trackers append


    //处理trackers，  ret.append ()  time_since_update>max_age trackers.pop

    //return 0
 


int main()
{
    SortObj *obj = &sortObj;
    Matrix *mat = &matrix;
    sort_default_param_set(obj);
    read_detection_data(obj);
    int length=sizeof(obj->num_frame)/sizeof(obj->num_frame[0]);
    int max_frame=get_number_of_frames(length,obj);
    obj->frame_flag=0;
    for(int i=1;i<=max_frame;i++)
    {
      obj->frame_count++;
      int number_of_id=0;
     //将第一帧的数据打包  x1 y1 x2 y2 id
     //记录当前帧有几个det
      while(obj->num_frame[obj->frame_flag] == i)
      {
        obj->frame_flag++;
        number_of_id++;
      }
      //将数据打包成数组
      double arr[number_of_id*5];
      for(int j=0,z=0;j<number_of_id;j++,z+=5)
      {
          int k=obj->frame_flag-number_of_id;
          arr[z+0]=obj->x[j+k];
          arr[z+1]=obj->y[j+k];
          arr[z+2]=obj->x[j+k]+obj->w[j+k];
          arr[z+3]=obj->y[j+k]+obj->h[j+k];
          arr[z+4]=obj->id[j+k];
          //printf("frame==%i,%lf,%lf,%lf,%lf,%lf\n",i,arr[z+0],arr[z+1],arr[z+2],arr[z+3],arr[z+4]);
      }
      //double arr[number_of_id][5];
      // for(int j=0;j<number_of_id;j++)
      // {
      //     int k=obj->frame_flag-number_of_id;
      //     arr[j][0]=obj->x[j+k];
      //     arr[j][1]=obj->y[j+k];
      //     arr[j][2]=obj->x[j+k]+obj->w[j+k];
      //     arr[j][3]=obj->y[j+k]+obj->h[j+k];
      //     arr[j][4]=obj->id[j+k];
      //     //printf("frame==%i,%lf,%lf,%lf,%lf,%lf\n",i,arr[j][0],arr[j][1],arr[j][2],arr[j][3],arr[j][4]);
      // }
      //将数组传入
       //矩阵初始化为0
       //printf("====%d\n",number_of_id);
       Matrix *mat_det=init_matrix(mat_det,number_of_id,5);
       print_matrix(mat_det);
       value_matrix(mat_det,arr);
       //print_matrix(mat_det);
       //

    }
    return 0;
}