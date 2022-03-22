#include <stdio.h>
#include "Hungarian.h"

void zeroout(MATRIX *hungary)
{
	int i,j; 
	int tem;	//表示同行的最小元素或同列的最小元素 
	for(i=1;i<=hungary->matrixsize;i++)             //减去同行最小元素
 	{ 
  	 	tem=hungary->cost[i][1];
  	 	for(j=2;j<=hungary->matrixsize;j++)
    	if(hungary->cost[i][j]<tem)
    		tem=hungary->cost[i][j];
  		for(j=1;j<=hungary->matrixsize;j++)
   		hungary->cost[i][j]=hungary->cost[i][j]-tem;
 	}
 	for(j=1;j<=hungary->matrixsize;j++)            //减去同列最小元素
 	{
  		tem=hungary->cost[1][j];
  		for(i=2;i<=hungary->matrixsize;i++)
     	if(hungary->cost[i][j]<tem)
    		tem=hungary->cost[i][j];
  		for(i=1;i<=hungary->matrixsize;i++)
  			hungary->cost[i][j]=hungary->cost[i][j]-tem;
 	}
}
void circlezero(MATRIX *hungary,assign *outforsort)
{
	int i,j,p;  
	int flag; 
 	for(i=0;i<=hungary->matrixsize;i++)                         //在矩阵外面构建半圈矩阵标记0的个数；
  		hungary->cost[i][0]=0; 
 	for(j=1;j<=hungary->matrixsize;j++)
  		hungary->cost[0][j]=0;
 	for(i=1;i<=hungary->matrixsize;i++)
  		for(j=1;j<=hungary->matrixsize;j++)
   		if(hungary->cost[i][j]==0)
   		{
    		hungary->cost[i][0]++;
    		hungary->cost[0][j]++;
    		hungary->cost[0][0]++;
   		} 
 	for(i=0;i<=hungary->matrixsize;i++)               //新建一个矩阵
  		for(j=0;j<=hungary->matrixsize;j++)           
   			hungary->zeroelem[i][j]=0;   
 	flag=hungary->cost[0][0]+1;                         //flag = 0的总个数+1
	while(hungary->cost[0][0]<flag)                   
	{
  		flag=hungary->cost[0][0];                                       //行列单0的情况，
  		for(i=1;i<=hungary->matrixsize;i++)                             //第一遍先行后列
	 	{
   			if(hungary->cost[i][0]==1) 
			{
				for(j=1;j<=hungary->matrixsize;j++)                        
     			if(hungary->cost[i][j]==0&&hungary->zeroelem[i][j]==0)
      				break;
    			hungary->zeroelem[i][j]=1;
    			hungary->cost[i][0]--;
   		 		hungary->cost[0][j]--;
    			hungary->cost[0][0]--;
    			if(hungary->cost[0][j]>0)
     			for(p=1;p<=hungary->matrixsize;p++)
      			if(hungary->cost[p][j]==0&&hungary->zeroelem[p][j]==0)
      			{
       				hungary->zeroelem[p][j]=2;
       				hungary->cost[p][0]--;
       				hungary->cost[0][j]--;
       				hungary->cost[0][0]--;
      			}      
			}                           
	
  		}
		for(j=1;j<=hungary->matrixsize;j++)                            //   第二遍先列后行
 		{
   			if(hungary->cost[0][j]==1)
			{
		    	for(i=1;i<=hungary->matrixsize;i++)
     			if(hungary->cost[i][j]==0&&hungary->zeroelem[i][j]==0)
      				break;
    			hungary->zeroelem[i][j]=1;
    			hungary->cost[i][0]--;
    			hungary->cost[0][j]--;
    			hungary->cost[0][0]--;
    			if(hungary->cost[i][0]>0)
     			for(p=1;p<=hungary->matrixsize;p++)
      			if(hungary->cost[i][p]==0&&hungary->zeroelem[i][p]==0)
      			{
       				hungary->zeroelem[i][p]=2;
       				hungary->cost[i][0]--;
       				hungary->cost[0][p]--;
       				hungary->cost[0][0]--;
      			}
			}
  		}
	}
	if(hungary->cost[0][0]>0)
		twozero(hungary,outforsort);
	else
		judge(hungary,outforsort);
}
void judge(MATRIX *hungary,assign *outforsort)
{
	int i,j;
 	int num=0;	//线的条数 
 	int start;	//每组解的储存开始位置 
 	for(i=1;i<=hungary->matrixsize;i++)
  		for(j=1;j<=hungary->matrixsize;j++)
   		if(hungary->zeroelem[i][j]==1)
    		num++;						//划线的条数 
		if(num==hungary->matrixsize)
		{
  			start=outforsort->result[0][0]*hungary->matrixsize+1;
   			for(i=1;i<=hungary->matrixsize;i++)
    			for(j=1;j<=hungary->matrixsize;j++)
     				if(hungary->zeroelem[i][j]==1)
     				{
      					outforsort->result[start][0]=i;
      					outforsort->result[start++][1]=j;
     				}
   					outforsort->result[0][0]++;
  		}
 		else
  			refresh(hungary,outforsort);
}
void twozero(MATRIX *hungary,assign *outforsort)
{
	int i,j;
	int p,q;
	int m,n;
	int flag;
    MATRIX backup;
	for(i=1;i<=hungary->matrixsize;i++)
		if(hungary->cost[i][0]>0)
			break;
	if(i<=hungary->matrixsize)
	{
		for(j=1;j<=hungary->matrixsize;j++)
		{
			backup=*hungary;//备份以寻找多解 
			if(hungary->cost[i][j]==0&&hungary->zeroelem[i][j]==0)
			{
    			hungary->zeroelem[i][j]=1;
    			hungary->cost[i][0]--;
    			hungary->cost[0][j]--;
    			hungary->cost[0][0]--;
    			for(q=1;q<=hungary->matrixsize;q++)
     				if(hungary->cost[i][q]==0&&hungary->zeroelem[i][q]==0)
     				{
      					hungary->zeroelem[i][q]=2;
      					hungary->cost[i][0]--;
      					hungary->cost[0][q]--;
      					hungary->cost[0][0]--;
     				}
    			for(p=1;p<=hungary->matrixsize;p++)
     				if(hungary->cost[p][j]==0&&hungary->zeroelem[p][j]==0)
     				{
      					hungary->zeroelem[p][j]=2;
      					hungary->cost[p][0]--;
      					hungary->cost[0][j]--;
      					hungary->cost[0][0]--;
     				}
    			flag=hungary->cost[0][0]+1;
    			while(hungary->cost[0][0]<flag)
    			{
     				flag=hungary->cost[0][0];
     				for(p=i+1;p<=hungary->matrixsize;p++)
     				{
     			 		if(hungary->cost[p][0]==1)
						{
       						for(q=1;q<=hungary->matrixsize;q++)
        						if(hungary->cost[p][q]==0&&hungary->zeroelem[p][q]==0)
         							break;
       							hungary->zeroelem[p][q]=1;
       							hungary->cost[p][0]--;
       							hungary->cost[0][q]--;
       							hungary->cost[0][0]--;
       						for(m=1;m<=hungary->matrixsize;m++)
        						if(hungary->cost[m][q]==0&&hungary->zeroelem[m][q]==0)
        						{
        			 				hungary->zeroelem[m][q]=2;
         							hungary->cost[m][0]--;
         							hungary->cost[0][q]--;
         							hungary->cost[0][0]--;
        						}
      					}
     				}
     				for(q=1;q<=hungary->matrixsize;q++)
     				{
      					if(hungary->cost[0][q]==1)
						{
       						for(p=1;p<=hungary->matrixsize;p++)
        						if(hungary->cost[p][q]==0&&hungary->zeroelem[p][q]==0)
         							break;
       							hungary->zeroelem[p][q]=1;
       							hungary->cost[p][q]--;
       							hungary->cost[0][q]--;
       							hungary->cost[0][0]--;
       						for(n=1;n<=hungary->matrixsize;n++)
        						if(hungary->cost[p][n]==0&&hungary->zeroelem[p][n]==0)
								{
         							hungary->zeroelem[p][n]=2;
         							hungary->cost[p][0]--;
         							hungary->cost[0][n]--;
         							hungary->cost[0][0]--;
        						}
      					}
     				}
    			}
    			if(hungary->cost[0][0]>0)                   //确保hungary.cost[][]中的0元素都在zeroelem[][]中被完全标记出来。
     				twozero(hungary,outforsort);
    			else 
     				judge(hungary,outforsort);
   			}           
   			hungary=&backup;
  		}
 	}
}
void refresh(MATRIX *hungary,assign *outforsort)
{
	int i,j,min=0;
	int flag1=0,flag2=0;
	for(i=1;i<=hungary->matrixsize;i++)
	{
		for(j=1;j<=hungary->matrixsize;j++)
		if(hungary->zeroelem[i][j]==1)
		{
			hungary->zeroelem[i][0]=1;         //有独立零元素
    		break;
   		}
	}
	while(flag1==0)
	{
		flag1=1;
		for(i=1;i<=hungary->matrixsize;i++)
			if(hungary->zeroelem[i][0]==0)
			{
				hungary->zeroelem[i][0]=2;
				for(j=1;j<=hungary->matrixsize;j++)
					if(hungary->zeroelem[i][j]==2)
					{
						hungary->zeroelem[0][j]=1;
					}
   			}
		for(j=1;j<=hungary->matrixsize;j++)
		{
			if(hungary->zeroelem[0][j]==1)
			{
				hungary->zeroelem[0][j]=2;
				for(i=1;i<=hungary->matrixsize;i++)
    				if(hungary->zeroelem[i][j]==1)
					{
						hungary->zeroelem[i][0]=0;
      					flag1=0;
     				}
   			}
  		}
 	}                    //对打勾的行和列标记成2 
	for(i=1;i<=hungary->matrixsize;i++)
	{
		if(hungary->zeroelem[i][0]==2)
		{
			for(j=1;j<=hungary->matrixsize;j++)
			{
    			if(hungary->zeroelem[0][j]!=2)
     				if(flag2==0)
     				{
     				 	min=hungary->cost[i][j];
      					flag2=1;
     				}
     			else
				{
      				if(hungary->cost[i][j]<min)
       					min=hungary->cost[i][j];
     			}
   			}        
  		}
 	}					//寻找未被覆盖的最小值 
	for(i=1;i<=hungary->matrixsize;i++)
	{
		if(hungary->zeroelem[i][0]==2)
			for(j=1;j<=hungary->matrixsize;j++)
				hungary->cost[i][j]=hungary->cost[i][j]-min;
	}
	for(j=1;j<=hungary->matrixsize;j++)
	{
		if(hungary->zeroelem[0][j]==2)
			for(i=1;i<=hungary->matrixsize;i++)
				hungary->cost[i][j]=hungary->cost[i][j]+min;
	}                   //未被划线的行减去未被覆盖的最小值，被划线的列加上未被覆盖的最小值 
	for(i=0;i<=hungary->matrixsize;i++)
		for(j=0;j<=hungary->matrixsize;j++)
			hungary->zeroelem[i][j]=0;              //矩阵清0
	circlezero(hungary,outforsort); 
}

void output(DatatoKL *Output){
	// printf("%d\n",Output->m);
	for(int i = 0; i < Output->m; i++){
		printf("%d to %d\n",Output->matched_indices[i][0],Output->matched_indices[i][1]);
	}
	for(int i = 0; i < Output->undetections; i++){
		printf("undetections:%d\n",Output->unmatched_detections[i]);
	}
	for(int i = 0; i < Output->untrackers; i++){
		printf("untrackers:%d\n",Output->unmatched_trackers[i]);
	}
}

//生成车位点数据
void getdata(box_data *box_data, box b)
{
    box_data->b[(box_data->number)].x = b.x;
    box_data->b[(box_data->number)].y = b.y;
    box_data->b[(box_data->number)].w = b.w;
    box_data->b[(box_data->number)].h = b.h;
    box_data->b[(box_data->number)].x1 = b.x1;
    box_data->b[(box_data->number)].y1 = b.y1;
    box_data->b[(box_data->number)].x2 = b.x2;
    box_data->b[(box_data->number)].y2 = b.y2;
    box_data->number++;
}
//生成iou函数
void pks_box_iou(box_data *model_data, box_data *track_data, IOU *iou_data){
    for(int i = 0; i < model_data->number; i ++){
        for(int j  = 0; j < track_data->number; j++){
            float track_area;
            float model_area;
            float sum_area;
            float xx1;
            float yy1;
            float xx2;
            float yy2;
            xx1 = model_data->b[i].x1 > track_data->b[j].x1 ? model_data->b[i].x1:track_data->b[j].x1;
            yy1 = model_data->b[i].y1 > track_data->b[j].y1 ? model_data->b[i].y1:track_data->b[j].y1;
            xx2 = model_data->b[i].x2 < track_data->b[j].x2 ? model_data->b[i].x2:track_data->b[j].x2;
            yy2 = model_data->b[i].y2 < track_data->b[j].y2 ? model_data->b[i].y2:track_data->b[j].y2;

            track_area = track_data->b[i].h * track_data->b[i].w;
            model_area = model_data->b[j].h * model_data->b[j].w;
            sum_area = track_area + model_area - ((xx2-xx1) > 0 ? (xx2-xx1):0) * ((yy2-yy1) > 0 ? (yy2-yy1):0);
            float o;
            o = ((xx2-xx1) > 0 ? (xx2-xx1):0) * ((yy2-yy1) > 0 ? (yy2-yy1):0)/ sum_area;
            iou_data->iou[i][j] = o;
        }
    }
}
//传给匈牙利匹配的iou数据
void data_to_hungarian(box_data *model_data, box_data *track_data, IOU *iou_data, Datahungarian *data){
    for(int i = 0; i < model_data->number;i++){
        for (int j = 0 ; j < track_data->number;j++){
            data->datatohungarian[i][j] = iou_data->iou[i][j];
		}
	}
	if(model_data->number>track_data->number){
		data->num = model_data->number;
		int tmp = 0;
		tmp = model_data->number-track_data->number;
		for(int j = 0; j < model_data->number; j++){
			for(int i = tmp; i < model_data->number;i++){
				data->datatohungarian[j][i] = 0;
			}
		}
	}
	else if(model_data->number<track_data->number){
		data->num = track_data->number;
		int tmp = 0;
		tmp = track_data->number-model_data->number;
		for(int j = tmp; j < track_data->number; j++){
			for(int i = 0; i < track_data->number;i++){
				data->datatohungarian[j][i] = 0;
			}
		}
	}
	else{data->num = model_data->number;}
}

//判断匹配的IOU数据，无匈牙利部分  
void assign_index(DatatoKL *Output,box_data *model_box_data, box_data *track_box_data, IOU *iou_data)
{
	Output->m = 0;
	for(int i = 0; i < model_box_data->number;i++)
    {
        for (int j = 0 ; j < track_box_data->number;j++)
        {
            if(iou_data->iou[i][j] == 1){
				Output->matched_indices[Output->m][0] = i;
				Output->matched_indices[Output->m][1] = j;
				Output->m++;
            }
        }
    }
}

//判断未assign和未tracker
void undet_untrack(DatatoKL *Output,box_data *model_data, box_data *track_data){
	int undet[20] = {0};
	int untracker[20] = {0};
	Output->undetections = 0;
	Output->untrackers = 0;
	for(int i = 0;i < model_data->number; i++){
		undet[Output->matched_indices[i][0]] = 1;
	}
	for(int j = 0;j < track_data->number; j++){
		untracker[Output->matched_indices[j][1]] = 1;
	}
	for(int i = 0; i < model_data->number; i++){
		if(undet[i] == 0){
			Output->unmatched_detections[Output->undetections] = i;
			Output->undetections++;
		}
	}
	for(int j = 0; j < track_data->number; j++){
		if(untracker[j] == 0){
			Output->unmatched_trackers[Output->untrackers] = j;
			Output->untrackers++;
		}
	}
}


//判断匹配数据，带匈牙利
void hungarian_assign(DatatoKL *Output, assign *outforsort,MATRIX *hungary,IOU *iou_data){
	Output->m = 0;
	for(int j=1;j<1+hungary->matrixsize;j++)
    {	
		// printf("%d,%d\n",outforsort->result[j][0],outforsort->result[j][1]);
		if(iou_data->iou[outforsort->result[j][0]-1][outforsort->result[j][1]-1] == 1){
			Output->matched_indices[Output->m][0] = outforsort->result[j][0]-1;
			Output->matched_indices[Output->m][1] = outforsort->result[j][1]-1;
			Output->m++;
		}
	}
}

//简单情况输出
void assign_output(DatatoKL *Output,box_data *model_data, box_data *track_data, IOU *iou_data){
	assign_index(Output,model_data, track_data, iou_data);
	undet_untrack(Output,model_data, track_data);
	output(Output);
}

//匈牙利输出
void hungarian_assign_output(box_data *model_data, box_data *track_data, IOU *iou_data, Datahungarian *data,DatatoKL *Output, assign *outforsort,MATRIX *hungary)
{
	data_to_hungarian(model_data, track_data, iou_data, data);
	hungary->matrixsize = data->num;
        for(int i=1;i<=hungary->matrixsize;i++)
		for(int j=1;j<=hungary->matrixsize;j++)
		{   
			hungary->cost[i][j] = -data->datatohungarian[i-1][j-1]+10000;
			hungary->costforout[i][j]=hungary->cost[i][j];
		}
        outforsort->result[0][0]=0;
		zeroout(hungary);
        circlezero(hungary,outforsort); 
        hungarian_assign(Output,outforsort,hungary,iou_data);
        undet_untrack(Output,model_data,track_data);
        output(Output);
}

//匈牙利总程序(不包含初始化车位信息)
void Hungarian(box_data *model_data, box_data *track_data, IOU *iou_data, Datahungarian *data,DatatoKL *Output, assign *outforsort,MATRIX *hungary,SortObj *sort)
{
	pks_box_iou(model_data, track_data, iou_data);
	for(int i = 0; i < model_data->number;i++) //赋值整数后的IOU矩阵
    {
        for (int j = 0 ; j < track_data->number;j++)
        {
            if(iou_data->iou[i][j] > sort->iou_threshold){
                iou_data->iou[i][j] = 1;
                printf("%f ",iou_data->iou[i][j]);
            }
            if(iou_data->iou[i][j] <= sort->iou_threshold){
                iou_data->iou[i][j] = 0;
                printf("%f ",iou_data->iou[i][j]);
            }
            if(j == track_data->number-1){
                printf("\n");
            }
        }
    }

	int maxrow = 0;
    int maxcol = 0;
    int row = 0;
    int col = 0;
    for(int i = 0; i < model_data->number; i++){
        int sumrow = 0;
        for(int j = 0; j < track_data->number; j++){
            sumrow = sumrow + iou_data->iou[i][j];
        }
        if(sumrow > maxrow){
            maxrow = sumrow;
        }
    }
    if(maxrow == 1){
        row = 1;
    }

    for(int i = 0; i < track_data->number; i++){
        int sumcol = 0;
        for(int j = 0; j < model_data->number; j++){
            sumcol = sumcol + iou_data->iou[j][i];
        }
        if(sumcol > maxcol){
            maxcol = sumcol;
        }
    }
    if(maxcol == 1){
        col = 1;
    }

    if(maxcol == 1 && maxrow ==1){
        assign_output(Output,model_data, track_data, iou_data);
    }
    else{
        hungarian_assign_output(model_data, track_data, iou_data, data,Output,outforsort,hungary);
    }
}