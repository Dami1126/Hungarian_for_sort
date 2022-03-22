#ifndef HUNGARIAN_H
#define HUNGARIAN_H

typedef struct
{
// int num_frame[row],id[row],ii[row];
// double x[row],y[row],w[row],h[row];
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
	int cost[15][15];  //cost矩阵
	int zeroelem[15][15]; //零元素矩阵
 	int costforout[15][15]; //用于输出结果的矩阵
 	int matrixsize; //矩阵阶数
}MATRIX;

typedef struct 
{
	int result[25][2];
}assign;

//定义车位点结构体
typedef struct
{
    double x1,y1,w,h,x,y,x2,y2;
}box;

typedef struct 
{
    int number;
    box b[15];
}box_data;
//定义iou二维数组结构体
typedef struct 
{
    float iou[15][15];
}IOU;

typedef struct 
{
    float datatohungarian[15][15];
    int num;
}Datahungarian;

typedef struct 
{
    int m;//已匹配个数
    int undetections;//未匹配个数
    int untrackers;//未追踪个数
    int matched_indices[20][2]; //匹配上的数组
    int unmatched_detections[20];//未匹配的数组
    int unmatched_trackers[20];//为追踪的数组
}DatatoKL;  //用于最后输出给卡尔曼的结构体


SortObj sort;
MATRIX hungary;
assign outforsort;
box_data model_box_data,track_box_data;
box model_box, track_box;
IOU iou_data;
Datahungarian data_hungarian;
DatatoKL Output;
void zeroout(MATRIX *hungary);						//减去行列的最小值得到零元素 
void circlezero(MATRIX *hungary,assign *outforsort);					//圈出单行列零元素 
void twozero(MATRIX *hungary,assign *outforsort);						//圈出行列存在两个以上的零元素 
void judge(MATRIX *hungary,assign *outforsort);	//判断是否符合匈牙利算法条件 
void refresh(MATRIX *hungary,assign *outforsort);						//不符合条件，对矩阵进行变形 

void output(DatatoKL *Output);	//打印结果输出 
void getdata(box_data *box_data, box b); //得到车位数据
void pks_box_iou(box_data *track_data, box_data *model_data, IOU *iou_data); //计算IOU
void data_to_hungarian(box_data *model_data, box_data *track_data, IOU *iou_data, Datahungarian *data);//传给匈牙利匹配的iou数据

void assign_index(DatatoKL *Output,box_data *model_data, box_data *track_data, IOU *iou_data); //判断匹配的IOU数据，无匈牙利部分  
void undet_untrack(DatatoKL *Output,box_data *model_data, box_data *track_data);//判断未assign和未tracker

void hungarian_assign(DatatoKL *Output, assign *outforsort,MATRIX *hungary,IOU *iou_data);//判断匹配数据，带匈牙利

void assign_output(DatatoKL *Output,box_data *model_data, box_data *track_data, IOU *iou_data);//简单情况输出
void hungarian_assign_output(box_data *model_data, box_data *track_data, IOU *iou_data, Datahungarian *data,DatatoKL *Output, assign *outforsort,MATRIX *hungary);//匈牙利输出

void Hungarian(box_data *model_data, box_data *track_data, IOU *iou_data, Datahungarian *data,DatatoKL *Output, assign *outforsort,MATRIX *hungary,SortObj *sort);//匈牙利总程序(不包含初始化车位信息)



#endif