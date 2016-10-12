/*-------头文件---------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <ctype.h>
#define NAME    "root"
#define PWD     "123456"

/*采购运输基本信息*/
typedef struct transport TRANS;
struct transport{
    char pur_num[5];                     /*采购企业编号*/
    char sup_num[5];                     /*供货企业编号*/
    char ship_num[4];                    /*运输船只编号*/
    char ship_name[10];                  /*运输船只名称*/
    int trans_num;                       /*运输数量*/
    float trans_money;                   /*价值金额*/
    float grade_mine;                    /*矿石品位*/
    TRANS *next;                         /*指向下一节点的指针*/
    GtkTreeIter iter;       /*treeview中对应treeiter*/
};


/*供货企业供货基本信息*/
typedef struct supply_companys SUP_COM;
struct supply_companys{
    char pur_num[5];                     /*采购企业编号*/
    char sup_num[5];                     /*供货企业编号*/
    char sup_name[20];                   /*供货企业名称*/
    int sup_mile;                        /*海运里程*/
    int sup_month_num;                   /*当月采购数量*/
    float sup_month_money;               /*当月采购金额*/
    int sup_total_num;                   /*累计采购数量*/
    float sup_total_money;               /*累计采购金额*/
    float grade_mine;                    /*铁矿石平均品位*/
    SUP_COM *next;                       /*指向下一节点的指针*/
    TRANS *tnext;                        /*指向采购运输基本信息的指针*/
    GtkTreeIter iter;
};


/*采购企业铁矿石采购基本信息*/
typedef struct purchase_companys PUR_COM;
struct purchase_companys{
    char pur_num[5];                     /*采购企业编号*/
    char pur_name[20];                   /*采购企业名称*/
    int pur_plan_num;                    /*计划采购数量*/
    float pur_plan_money;                /*计划采购金额*/
    int pur_month_num;                   /*当月采购数量*/
    float pur_month_money;               /*当月采购金额*/
    int pur_total_num;                   /*累积采购数量*/
    float pur_total_money;               /*累计采购金额*/
    PUR_COM *next;                       /*指向下一节点的指针*/
    SUP_COM *snext;                      /*指向供货企业基本信息的指针*/
    GtkTreeIter iter;
};

/**将登陆窗体独立成一个结构体*/
struct login_widget
{
    GtkWidget *window; //主窗体
    GtkWidget *label_tips; //用于信息提示的标签
    GtkWidget *button_login; //两个按钮，一个点击后登录，一个点击后退出
    GtkWidget *button_exit;
    GtkWidget *entry_username; //两个文本框，用于输入用户名和密码
    GtkWidget *entry_pwd;
    GtkWidget *label_username; //两个标签用于显示username文本框和password文本框提示
    GtkWidget *label_pwd;
    GtkWidget *vbox; //垂直布局盒子，包含以下三个水平布局盒子
    GtkWidget *hbox_username; //包含用户名提示标签和用户名文本框，下面的HBOX作用类似
    GtkWidget *hbox_pwd;
    GtkWidget *hbox_button;
} wgt;


typedef union nodep        /*指向节点的指针联合*/
{
    TRANS *trans;
    SUP_COM *sup;
    PUR_COM *pur;
} nodep;

struct nodecreate        /*传递参数*/
{
    GtkWidget *window;
    GtkWidget *entry[9];
    nodep unp;
    int type;
};

struct query_judge        /*传递参数*/
{
    GtkWidget *entry;
    int flag;
};

/********************
 全局变量
 *********************/
GtkWidget *window;          /*主界面窗口*/
GtkWidget *showlist;       /*显示属性的位置*/
GtkListStore *liststore;
GtkListStore *lstore[3];      /*显示栏左边项目名liststore组*/
GtkTreeStore *treestore;          /*树形储存*/
GtkWidget *treeview;        /*树状列表目录*/
GtkTreeIter rootiter;      /*根位置*/
GtkTreeIter selectediter;  /*选中的位置*/

/*显示属性liststore的控件组*/
GtkTreeIter pur_iter[8];
GtkTreeIter sup_iter[9];
GtkTreeIter trans_iter[7];

PUR_COM *gp_head;              /*主链头指针*/
char **Str_Pointer[3];
void (*query_node[3])();


/*全局变量*/
extern char *gp_pur_info_filename;
extern char *gp_sup_info_filename;
extern char *gp_trans_info_filename;
extern char *Node_Str[];
extern int NODE_INS[];
extern char *pur_Str[];
extern char *sup_Str[];
extern char *trans_Str[];


enum //iter里的列号
{
    COLUMN = 0,
    COMMENT
} ;
enum
{
    TYPE_ROOT =1,
    TYPE_pur,
    TYPE_sup,
    TYPE_trans
} ;

/********************
 函数声明
 *********************/

void init_menubar(GtkWidget *menubar);
void create_view_and_model (void);
void init_show(GtkWidget *list);
void  on_changed(GtkWidget *widget, gpointer statusbar);


int LoadData(GtkWidget *button);
int LoadList(PUR_COM **phead);
void rebuildtree();
int SaveData(GtkWidget *button);
int SaveList(PUR_COM *phead);
void quit_save(GtkWidget *button);


void Add_node(GtkWidget *button,struct nodecreate *nodec);
PUR_COM * insert_SUP(SUP_COM *pNew);
SUP_COM *insert_TRANS(TRANS *pNew);
int DelNode(GtkWidget *button);
void Del_Node(GtkWidget *button);
int Del_pur(char *name);
int Del_sup(char *name, char *P_name);
int Del_trans(char *name, char *P_name, char *PP_name);
void Edit_Node(GtkWidget *button, struct nodecreate *nodec);


void dialog_info(char *show);
void entry_info(GtkWidget *button, int type);
int Edit_info(GtkWidget *button);
void Query_info(GtkWidget *button, int type);
void f_cancel(GtkWidget *button, GtkWidget *win);
gint Judge_NODE_Type(GtkTreeIter *iter);
int Show_Node(GtkTreeIter iter);
GtkListStore *Show_pur(char *name);
GtkListStore *Show_sup(char *name, char *P_name);
GtkListStore *Show_trans(char *name, char *P_name, char *PP_name);


void Query_pur(GtkWidget *button, struct query_judge *in);
void Query_sup(GtkWidget *button, struct query_judge *in);
void Query_trans(GtkWidget *button, struct query_judge *in);
void expand_select(GtkTreeIter iter);
PUR_COM *PUR_search(char *P_name);
SUP_COM *SUP_search(char *S_name, SUP_COM *SUP);
TRANS *TRANS_search(char *T_name, TRANS *Trans);

void statis_func1(GtkWidget *button);
void statis_func2(GtkWidget *button);
void statis_func3(GtkWidget *button);

void gtk_win_destroy(GtkWidget *widget, gpointer data);
void login(GtkWidget *widget, gpointer data);
void init_login_widget();

void help_about(GtkWidget *button);




/********************
 main函数
 *********************/

int main( int argc, char *argv[])
{
    GtkWidget *vbox = NULL;
    GtkWidget *hbox, *hbox2;

    GtkWidget *menubar;
    GtkWidget *scrolled;
    GtkWidget *remove;
    GtkWidget *edit;
    GtkWidget *statusbar;

    GtkTreeSelection *selection;

    gtk_init(&argc, &argv);

    Str_Pointer[0] = pur_Str;
    Str_Pointer[1] = sup_Str;
    Str_Pointer[2] = trans_Str;

    query_node[0] = Query_pur;
    query_node[1] = Query_sup;
    query_node[2] = Query_trans;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //TODO:登陆框，另存为
    /**主窗口*/
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 525);
    gtk_window_set_title(GTK_WINDOW(window), "海外矿石采购信息管理系统");
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    gtk_widget_realize (window);
    g_signal_connect (G_OBJECT(window), "destroy",
                      G_CALLBACK(quit_save), NULL);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    /**菜单栏*/
    menubar = gtk_menu_bar_new();
    init_menubar(menubar);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    /**滚动条*/
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER(vbox), hbox);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(scrolled),
                                         GTK_SHADOW_ETCHED_IN);
    vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER(hbox), vbox);
    gtk_widget_set_usize(GTK_WIDGET(vbox), 200, 500);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 10);

    /**目录*/
    create_view_and_model();//初始化treeview
    gtk_container_add(GTK_CONTAINER (scrolled), treeview);
    /**下方两按钮*/
    hbox2 = gtk_hbox_new(TRUE, 4);
    edit = gtk_button_new_with_label(" 编辑 ");
    g_signal_connect(G_OBJECT(edit),"clicked",
                     G_CALLBACK(Edit_info), NULL);
    remove = gtk_button_new_with_label(" 删除 ");
    g_signal_connect(G_OBJECT(remove),"clicked",
                     G_CALLBACK(Del_Node), NULL);
    gtk_box_pack_start(GTK_BOX(hbox2), edit, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), remove, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 3);

    /**展示区域*/
    showlist = gtk_tree_view_new();//全局变量

    vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (hbox), vbox);
    gtk_widget_set_usize(GTK_WIDGET(vbox), 500, 500);
    gtk_box_pack_start(GTK_BOX(vbox), showlist, TRUE, TRUE, 5);

    init_show(showlist);
    /**状态栏*/
    statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 5);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    g_signal_connect(selection, "changed",
                     G_CALLBACK(on_changed), statusbar);
    /**登陆栏*/
    init_login_widget();
    gtk_main();
    return 0;
}

/**************
 界面初始化
 **************/

/**初始化菜单栏*/
void init_menubar(GtkWidget *menubar)
{
    /**"文件"子菜单*/
    GtkWidget *file;
    GtkWidget *filemenu;
    GtkWidget *load;
    GtkWidget *save;
    GtkWidget *quit;

    file = gtk_menu_item_new_with_label("文件");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

    filemenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);

    load = gtk_menu_item_new_with_label("读取");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), load);
    save = gtk_menu_item_new_with_label("存储");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
    quit = gtk_menu_item_new_with_label("退出");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);

    g_signal_connect(G_OBJECT(load), "activate",
                     G_CALLBACK(LoadData), NULL);
    g_signal_connect(G_OBJECT(save), "activate",
                     G_CALLBACK(SaveData), NULL);
    g_signal_connect(G_OBJECT(quit), "activate",
                     G_CALLBACK(quit_save), NULL);

    /**"添加"子菜单*/
    GtkWidget *add_M;
    GtkWidget *add_menu;
    GtkWidget *add[3];



    add_M = gtk_menu_item_new_with_label("添加");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), add_M);

    add_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(add_M), add_menu);

    add[0] = gtk_menu_item_new_with_label("添加采购企业");
    gtk_menu_shell_append(GTK_MENU_SHELL(add_menu), add[0]);
    add[1] = gtk_menu_item_new_with_label("添加供货企业");
    gtk_menu_shell_append(GTK_MENU_SHELL(add_menu), add[1]);
    add[2] = gtk_menu_item_new_with_label("添加运输基本信息");
    gtk_menu_shell_append(GTK_MENU_SHELL(add_menu), add[2]);

    g_signal_connect(G_OBJECT(add[0]), "activate",
                     G_CALLBACK(entry_info), 2);
    g_signal_connect(G_OBJECT(add[1]), "activate",
                     G_CALLBACK(entry_info), 3);
    g_signal_connect(G_OBJECT(add[2]), "activate",
                     G_CALLBACK(entry_info), 4);

    /**"查询"子菜单*/
    GtkWidget *query_M;
    GtkWidget *query_menu;
    GtkWidget *query[3];

    query_M = gtk_menu_item_new_with_label("查询");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), query_M);

    query_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(query_M), query_menu);

    query[0] = gtk_menu_item_new_with_label("查询采购企业");
    gtk_menu_shell_append(GTK_MENU_SHELL(query_menu), query[0]);
    query[1] = gtk_menu_item_new_with_label("查询供货企业");
    gtk_menu_shell_append(GTK_MENU_SHELL(query_menu), query[1]);
    query[2] = gtk_menu_item_new_with_label("查询运输基本信息");
    gtk_menu_shell_append(GTK_MENU_SHELL(query_menu), query[2]);

    g_signal_connect(G_OBJECT(query[0]), "activate",
                     G_CALLBACK(Query_info), 2);
    g_signal_connect(G_OBJECT(query[1]), "activate",
                     G_CALLBACK(Query_info), 3);
    g_signal_connect(G_OBJECT(query[2]), "activate",
                     G_CALLBACK(Query_info), 4);

    /**"统计"子菜单*/
    GtkWidget *statistics_M;
    GtkWidget *statistics_menu;
    GtkWidget *statistics[3];

    statistics_M = gtk_menu_item_new_with_label("统计");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), statistics_M);

    statistics_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(statistics_M), statistics_menu);

    statistics[0] = gtk_menu_item_new_with_label("采购企业累积采购数量及金额");
    gtk_menu_shell_append(GTK_MENU_SHELL(statistics_menu), statistics[0]);
    statistics[1] = gtk_menu_item_new_with_label("运输船只总数量及金额");
    gtk_menu_shell_append(GTK_MENU_SHELL(statistics_menu), statistics[1]);
    statistics[2] = gtk_menu_item_new_with_label("供货企业总数目");
    gtk_menu_shell_append(GTK_MENU_SHELL(statistics_menu), statistics[2]);

    g_signal_connect(G_OBJECT(statistics[0]), "activate",
                     G_CALLBACK(statis_func1), NULL);
    g_signal_connect(G_OBJECT(statistics[1]), "activate",
                     G_CALLBACK(statis_func2), NULL);
    g_signal_connect(G_OBJECT(statistics[2]), "activate",
                     G_CALLBACK(statis_func3), NULL);


    /**"帮助"子菜单*/
    GtkWidget *help;
    GtkWidget *helpmenu;
    GtkWidget *about;

    help = gtk_menu_item_new_with_label("帮助");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);

    helpmenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);

    about = gtk_menu_item_new_with_label("相关信息");
    gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);

    g_signal_connect(G_OBJECT(about), "activate",
                     G_CALLBACK(help_about), NULL);
}

/**初始化目录*/
void create_view_and_model (void)
{
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer;
    GtkTreeModel *model;

    treeview = gtk_tree_view_new();

    col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "目录");
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer,
                                       "text", COLUMN);

    //添加model及rootiter
    treestore= gtk_tree_store_new(1,
                                  G_TYPE_STRING);
    gtk_tree_store_append(treestore, &rootiter, NULL);
    gtk_tree_store_set(treestore, &rootiter,
                       COLUMN, "海外矿石采购信息",
                       -1);

    model=GTK_TREE_MODEL(treestore);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
}

/**初始化显示栏*/
void init_show(GtkWidget *list)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    int i,j;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("信息",
                                                      renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    column = gtk_tree_view_column_new_with_attributes("内容",
                                                      renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    GtkTreeIter *Node_iter[3];
    Node_iter[0] = pur_iter;
    Node_iter[1] = sup_iter;
    Node_iter[2] = trans_iter;

    for(i=0; i<3; i++)
    {

        lstore[i] = gtk_list_store_new(2,
                                       G_TYPE_STRING,
                                       G_TYPE_STRING
                                       );
        for(j = 0; j<NODE_INS[i+2]; j++)
        {
            gtk_list_store_append(lstore[i], &Node_iter[i][j]);
            gtk_list_store_set(lstore[i], &Node_iter[i][j],
                               COLUMN, Str_Pointer[i][j],
                               -1);
        }

    }
    gtk_tree_view_set_model(GTK_TREE_VIEW(list),
                            GTK_TREE_MODEL(lstore[0]));
}

/**改变状态栏及显示栏*/
void  on_changed(GtkWidget *widget, gpointer statusbar)
{
    GtkTreeModel *model;
    char *value;

    if (gtk_tree_selection_get_selected(
                                        GTK_TREE_SELECTION(widget), &model, &selectediter))
    {
        gtk_tree_model_get(model, &selectediter, COLUMN, &value,  -1);
        gtk_statusbar_push(GTK_STATUSBAR(statusbar),
                           gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),
                                                        value), value);
        g_free(value);
        Show_Node(selectediter);
    }
}


/********************
 读取与存储
 *********************/

//函数名：LoadData
//功能：读取数据文件
//输入参数：
//返回值：re 的二进制前3位记录了三个数据文件是否成功打开，1为成功
int LoadData(GtkWidget *button)
{
    int re;
    re = LoadList(&gp_head);
    if(re == 28)
    {
        dialog_info("数据加载成功");
        rebuildtree();
    }
    else
        dialog_info("数据加载失败");
    return (re);
}

//函数名：LoadList
//功能：读取数据文件中数据到链表中
//输入参数：phead 单位节点头指针的地址
//返回值：re 的二进制前3位记录了三个数据文件是否成功打开，1为成功
int LoadList(PUR_COM **phead)
{
    PUR_COM *hd = NULL,*ppur;
    SUP_COM *psup;
    TRANS *ptrans;
    FILE *pFile;
    int find;
    int re = 0;
    if((pFile = fopen(gp_pur_info_filename,"rb")) == NULL)
    {
        printf("采购企业数据文件打开失败！\n");    //printf用于控制台调试
        return re;
    }
    printf("采购企业数据文件打开成功！\n");
    /*从数据文件中读宿舍楼信息数据，存入以后进先出方式建立的主链中*/
    while(!feof(pFile))
    {
        ppur = (PUR_COM*)calloc(1, sizeof(PUR_COM));
        fread(ppur,sizeof(PUR_COM), 1, pFile);
        if(!feof(pFile))
        {
            ppur->snext = NULL;
            ppur->next = hd;
            hd = ppur;
        }
    }
    fclose(pFile);
    if(hd == NULL)
    {
        printf("采购企业数据文件加载失败！\n");
        return re;
    }
    printf("采购企业文件加载成功！\n");
    *phead = hd;
    re += 4;
    if((pFile = fopen(gp_sup_info_filename,"rb")) == NULL)
    {
        printf("成果数据文件打开失败！\n");
        return re;
    }
    printf("成果数据文件打开成功！\n");
    re +=8;

    /*从数据文件中读取成果基本信息数据，存入主链对应结点的成果基本信息支链中*/
    while(!feof(pFile))
    {
        /*创建结点，存放从数据文件中读出的成果基本信息*/
        psup = (SUP_COM*)calloc(1,sizeof(SUP_COM));
        fread(psup,sizeof(SUP_COM),1,pFile);
        if(!feof(pFile))
        {
            psup->tnext = NULL;

            /*在主链上查找该采购企业对应的主链结点*/
            ppur = hd;
            while(ppur != NULL && strcmp(ppur->pur_num,psup->pur_num) != 0)
            {
                ppur = ppur->next;
            }

            /*如果找到，则将结点以后进先出方式插入采购企业息支链*/
            if(ppur != NULL)
            {
                psup->next=ppur->snext;
                ppur->snext=psup;
            }
            else  /*如果未找到，则释放所创建结点的内存空间*/
            {
                free(psup);
            }
        }
    }
    fclose(pFile);
    if((pFile = fopen(gp_trans_info_filename,"rb")) == NULL)
    {
        printf("采购运输数据文件打开失败！\n");
        return re;
    }
    printf("采购运输数据文件打开成功！\n");
    re += 16;

    /*从数据文件中读取供货企业数据，存其对应结点的支链中*/
    while (!feof(pFile))
    {
        /*创建结点，存放从数据文件中读出的信息*/
        ptrans = (TRANS *)calloc(1,sizeof(TRANS));
        fread(ptrans, sizeof(TRANS), 1, pFile);
        if(!feof(pFile))
        {
            /*查找支链上对应供货企业结点*/
            ppur = hd;
            find = 0;
            while (ppur != NULL && find == 0)
            {
                psup = ppur->snext;
                while (psup != NULL && find == 0)
                {
                    if ((strcmp(psup->sup_num, ptrans->sup_num) == 0))
                    {
                        find = 1;
                        break;
                    }
                    psup = psup->next;
                }
                ppur = ppur->next;
            }
            if (find)  /*如果找到，则将结点以后进先出方式插入支链中*/
            {
                ptrans->next = psup->tnext;
                psup->tnext = ptrans;
            }
            else /*如果未找到，则释放所创建结点的内存空间*/
            {
                free(ptrans);
            }
        }
    }
    fclose(pFile);
    printf("\n数据加载完成\n");
    return re;
}
//函数名：rebuildtree
//功能：将链表中节点添加到左侧树状列表中
//输入参数：
//返回值：
void rebuildtree()
{
    GtkTreeModel *model;
    PUR_COM *p1;
    SUP_COM *p2;
    TRANS *p3;
    for(p1=gp_head; p1 != NULL; p1 = p1->next)
    {
        gtk_tree_store_append(treestore, &p1->iter,&rootiter);   //添加条目
        gtk_tree_store_set(treestore ,&p1->iter,                 //设置新添加条目的文本显示
                            COLUMN,p1->pur_num,
                           -1);
        for(p2=p1->snext; p2 != NULL; p2 = p2->next)
        {
            gtk_tree_store_append(treestore, &p2->iter, &p1->iter);
            gtk_tree_store_set(treestore, &p2->iter,
                               COLUMN, p2->sup_num,
                               -1);
            for(p3 = p2->tnext; p3 != NULL; p3 = p3->next)
            {
                gtk_tree_store_append(treestore, &p3->iter, &p2->iter);
                gtk_tree_store_set(treestore, &p3->iter,
                                   COLUMN, p3->ship_num,
                                   -1);
            }
        }
    }
    model = GTK_TREE_MODEL(treestore);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
    g_object_unref(model);
}
//函数名：SaveData
//功能：存储数据文件
//输入参数：
//返回值：flag 的二进制前3位记录了三个数据文件是否成功打开，1为成功
int SaveData(GtkWidget *button)
{
    int flag = 0;
    flag=SaveList(gp_head);
    if(flag == 28)
    {
        dialog_info("数据保存成功");
    }
    else
        dialog_info("数据保存失败");
    return (flag);
}

//函数名：SaveData
//功能：将链表中数据存储在数据文件中
//输入参数：phead单位节点头指针
//返回值：flag 的二进制前3位记录了三个数据文件是否成功打开，1为成功
int SaveList(PUR_COM *phead)
{
    FILE *fout1,*fout2,*fout3;
    PUR_COM *p1 = phead;
    SUP_COM *p2;
    TRANS *p3;
    int flag = 0;
    if((fout1 = fopen(gp_pur_info_filename,"wb")) == NULL)
        return flag;
    flag += 4;
    if((fout2 = fopen(gp_sup_info_filename,"wb")) == NULL)
        return flag;
    flag += 8;
    if((fout3=fopen(gp_trans_info_filename,"wb")) == NULL)
        return flag;
    flag += 16;
    while(p1 != NULL)
    {
        fwrite(p1, sizeof(PUR_COM), 1, fout1);
        p2 = p1->snext;
        while(p2 != NULL)
        {
            fwrite(p2, sizeof(SUP_COM), 1, fout2);
            p3 = p2->tnext;
            while(p3 != NULL)
            {
                fwrite(p3, sizeof(TRANS), 1, fout3);
                p3 = p3->next;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    fclose(fout1);
    fclose(fout2);
    fclose(fout3);
    return (flag);
}
//函数名：quit_save
//功能：推出前提示保存
//输入参数：
//返回值：
void quit_save(GtkWidget *button)
{
    GtkWidget *dialog;
    int flag;
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_OK_CANCEL,
                                    "退出前是否保存当前状态？");
    flag=gtk_dialog_run(dialog);
    switch(flag)
    {
        case GTK_RESPONSE_OK:SaveList(gp_head);
        case GTK_RESPONSE_CANCEL:gtk_main_quit();
        default:;
    }
    gtk_widget_destroy(dialog);
}



//函数名：help_about
//功能： 弹出软件信息及作者信息
//输入参数：
//返回值：无
void help_about(GtkWidget *button)
{
    dialog_info("This is a information management system.\n\
                \n\
                Yin Hao's C programming language course design\n\
                \n\
                Class: CS1507     Stu'ID:U201514653");
}


/*********************
 弹窗函数
 *********************/

//函数名：dialog_info
//功能：弹出一个消息框
//输入参数：show 要显示的字符串
//返回值：无
void dialog_info(char *show)//TODO:查询窗口底层问题
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    show, "title");
    gtk_window_set_title(GTK_WINDOW(dialog), "通知");
    gtk_window_set_keep_above (GTK_WINDOW(dialog), 1);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

//函数名：entry_info
//功能：弹出一个输入框
//输入参数：type对应枚举的几种类型
//返回值：无
void entry_info(GtkWidget *button,int type)
{
    GtkWidget *entry_window;
    GtkWidget *label,*b_ok,*b_cancel;
    GtkWidget *table;
    GtkWidget *vbox;
    GtkWidget *entry[9];
    struct nodecreate *nodec;
    int i;

    entry_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(entry_window, 350, 300);
    gtk_window_set_title(GTK_WINDOW(entry_window), "输入新节点数据");
    g_signal_connect(G_OBJECT(entry_window),"destroy",
                     G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_window_set_position(GTK_WINDOW(entry_window), GTK_WIN_POS_CENTER);
    gtk_window_set_keep_above (GTK_WINDOW(entry_window), 1);

    vbox = gtk_vbox_new (FALSE, 12);
    gtk_container_add (GTK_CONTAINER (entry_window), vbox);
    //传递几个重要参数给下一个函数而设计的结构
    nodec = (struct nodecreate *)malloc(sizeof(struct nodecreate));

    table = gtk_table_new(NODE_INS[type]+1, 7, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 10);

    for(i = 0; i < NODE_INS[type]; i++)
    {
        label = gtk_label_new(Str_Pointer[type-2][i]);
        gtk_table_attach(GTK_TABLE(table), label, 1, 3, i, i+1,
                         GTK_EXPAND, GTK_EXPAND, 0, 0);
        entry[i] = gtk_entry_new();
        gtk_table_attach(GTK_TABLE(table), entry[i], 3, 7, i, i+1,
                         GTK_EXPAND, GTK_EXPAND, 0, 0);
        nodec->entry[i] = entry[i];
    }

    nodec->window = entry_window;
    nodec->type = type;

    b_ok = gtk_button_new_with_label("确定");
    g_signal_connect(G_OBJECT(b_ok), "clicked", G_CALLBACK(Add_node), nodec);
    gtk_table_attach(GTK_TABLE(table), b_ok, 1, 2, NODE_INS[type], NODE_INS[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    b_cancel = gtk_button_new_with_label("取消");
    g_signal_connect(G_OBJECT(b_cancel), "clicked", G_CALLBACK(f_cancel), entry_window);
    gtk_table_attach(GTK_TABLE(table), b_cancel, 5, 6, NODE_INS[type], NODE_INS[type]+1,
                     GTK_EXPAND, GTK_EXPAND, 0, 0);
    gtk_widget_show_all(entry_window);
}

//函数名：Edit_info
//功能：弹出一个编辑框
//输入参数：
//返回值：无
int Edit_info(GtkWidget *button)
{
    GtkWidget *edit_window;
    GtkWidget *label,*b_ok,*b_cancel;
    GtkWidget *table;
    GtkWidget *vbox;
    GtkWidget *entry[9];
    struct nodecreate *nodec;
    int i;
    int type;

    type = Judge_NODE_Type(&selectediter);
    if(type == TYPE_ROOT||type == 0)
    {
        dialog_info("ROOT节点无法编辑！");
        return 1;
    }

    edit_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(edit_window, 400, 300);
    g_signal_connect(G_OBJECT(edit_window), "destroy",
                     G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_window_set_position(GTK_WINDOW(edit_window), GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new (FALSE, 12);
    gtk_container_add (GTK_CONTAINER (edit_window), vbox);

    nodec = (struct nodecreate *)malloc(sizeof(struct nodecreate));

    table = gtk_table_new(NODE_INS[type]+1, 7, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 10);

    for(i = 0; i < NODE_INS[type]; i++)
    {
        label = gtk_label_new((Str_Pointer[type-2][i]));
        gtk_table_attach(GTK_TABLE(table), label, 1, 3, i, i+1,
                         GTK_EXPAND, GTK_EXPAND, 0, 0);
        entry[i] = gtk_entry_new();
        gtk_table_attach(GTK_TABLE(table),entry[i], 3, 7, i, i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        nodec->entry[i] = entry[i];
    }
    //获取节点名称并设置为标题
    GtkTreeModel *model;
    GtkTreePath *path;
    GtkTreeIter iter;//不能直接声名指针

    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    path= gtk_tree_model_get_path(model, &selectediter);

    char *name;
    gtk_tree_model_get (model,&selectediter,
                        COLUMN, &name,
                        -1);

    gtk_window_set_title(GTK_WINDOW(edit_window), name);

    switch(type)
    {
        case TYPE_pur:
        {
            PUR_COM *ppur;
            char str[20];
            ppur = PUR_search(name);
            gtk_entry_set_text(GTK_ENTRY(entry[0]), "此项不可更改");
            gtk_entry_set_text(GTK_ENTRY(entry[1]), ppur->pur_name);
            sprintf(str,"%d", ppur->pur_plan_num);
            gtk_entry_set_text(GTK_ENTRY(entry[2]), str);
            sprintf(str,"%.2f", ppur->pur_plan_money);
            gtk_entry_set_text(GTK_ENTRY(entry[3]), str);
            sprintf(str,"%d", ppur->pur_month_num);
            gtk_entry_set_text(GTK_ENTRY(entry[4]), str);
            sprintf(str,"%.2f", ppur->pur_month_money);
            gtk_entry_set_text(GTK_ENTRY(entry[5]), str);
            sprintf(str,"%d", ppur->pur_total_num);
            gtk_entry_set_text(GTK_ENTRY(entry[6]), str);
            sprintf(str,"%d",ppur->pur_total_money);
            gtk_entry_set_text(GTK_ENTRY(entry[7]), str);
            nodec->unp.pur = ppur;
            break;
        }
        case TYPE_sup:
        {
            char *p_name;
            gtk_tree_path_up(path);
            gtk_tree_model_get_iter(model,&iter, path);
            gtk_tree_model_get (model,&iter,
                                COLUMN, &p_name,
                                -1);
            PUR_COM *ppur;
            ppur = PUR_search(p_name);
            SUP_COM *psup;
            psup = SUP_search(name, ppur->snext);
            char str[20];
            gtk_entry_set_text(GTK_ENTRY(entry[0]), "此项不可更改");
            gtk_entry_set_text(GTK_ENTRY(entry[1]), "此项不可更改");
            gtk_entry_set_text(GTK_ENTRY(entry[2]), psup->sup_name);
            sprintf(str,"%d", psup->sup_mile);
            gtk_entry_set_text(GTK_ENTRY(entry[3]), str);
            sprintf(str,"%d", psup->sup_month_num);
            gtk_entry_set_text(GTK_ENTRY(entry[4]), str);
            sprintf(str,"%.2f", psup->sup_month_money);
            gtk_entry_set_text(GTK_ENTRY(entry[5]), str);
            sprintf(str,"%d", psup->sup_total_num);
            gtk_entry_set_text(GTK_ENTRY(entry[6]), str);
            sprintf(str,"%.2f", psup->sup_total_money);
            gtk_entry_set_text(GTK_ENTRY(entry[7]), str);
            sprintf(str,"%.2f", psup->grade_mine);
            gtk_entry_set_text(GTK_ENTRY(entry[8]), str);
            nodec->unp.sup=psup;
            break;
        }
        case TYPE_trans:
        {
            char *P_name,*PP_name;
            gtk_tree_path_up(path);
            gtk_tree_model_get_iter(model, &iter,path);
            gtk_tree_model_get (model, &iter,
                                COLUMN, &P_name,
                                -1);
            gtk_tree_path_up(path);
            gtk_tree_model_get_iter(model, &iter,path);
            gtk_tree_model_get (model, &iter,
                                COLUMN, &PP_name,
                                -1);
            PUR_COM *ppur;
            ppur = PUR_search(PP_name);
            SUP_COM *psup;
            psup = SUP_search(P_name, ppur->snext);
            TRANS *ptrans;
            ptrans = TRANS_search(name, psup->tnext);

            char str[20];
            gtk_entry_set_text(GTK_ENTRY(entry[0]), "此项不可更改");
            gtk_entry_set_text(GTK_ENTRY(entry[1]), "此项不可更改");
            gtk_entry_set_text(GTK_ENTRY(entry[2]), "此项不可更改");
            gtk_entry_set_text(GTK_ENTRY(entry[3]), ptrans->ship_name);
            sprintf(str,"%d", ptrans->trans_num);
            gtk_entry_set_text(GTK_ENTRY(entry[4]), str);
            sprintf(str,"%.2f", ptrans->trans_money);
            gtk_entry_set_text(GTK_ENTRY(entry[5]), str);
            sprintf(str,"%.2f", ptrans->grade_mine);
            gtk_entry_set_text(GTK_ENTRY(entry[6]), str);
            nodec->unp.trans = ptrans;
            break;
        }
    }

    nodec->window = edit_window;
    nodec->type = type;

    b_ok=gtk_button_new_with_label("确定");
    g_signal_connect(G_OBJECT(b_ok),"clicked", G_CALLBACK(Edit_Node), nodec);
    gtk_table_attach(GTK_TABLE(table),b_ok, 1, 2, NODE_INS[type], NODE_INS[type]+1,
                     GTK_EXPAND, GTK_EXPAND, 0, 0);
    b_cancel=gtk_button_new_with_label("取消");
    g_signal_connect(G_OBJECT(b_cancel), "clicked", G_CALLBACK(f_cancel), edit_window);
    gtk_table_attach(GTK_TABLE(table),b_cancel, 5, 6, NODE_INS[type], NODE_INS[type]+1,
                     GTK_EXPAND, GTK_EXPAND, 0, 0);
    gtk_widget_show_all(edit_window);
};

//函数名：Query_info
//功能：根据type弹出一个查询框,再分别调用对应的Query函数
//输入参数：type对应枚举的几种类型
//返回值：无
void Query_info(GtkWidget *button,int type)
{
    GtkWidget *query_window;
    GtkWidget *label,*b_query,*b_next,*b_cancel;
    GtkWidget *table;
    GtkWidget *vbox;
    GtkWidget *entry;

    query_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(query_window, 300, 100);
    g_signal_connect(G_OBJECT(query_window), "destroy",
                     G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_window_set_position(GTK_WINDOW(query_window), GTK_WIN_POS_CENTER);
    gtk_window_set_keep_above (query_window, 1);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (query_window), vbox);
    table = gtk_table_new(2,7,TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 10);

    label = gtk_label_new("查询：");
    gtk_table_attach(GTK_TABLE(table), label, 0, 3, 0, 1,
                     GTK_EXPAND, GTK_EXPAND, 0, 0);
    entry = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table),entry, 3, 6, 0, 1,
                     GTK_EXPAND, GTK_EXPAND, 0, 0);
    //配置不同窗口标题
    char all_title[40];
    char *title[] = {"采购企业", "供货企业", "采购运输基本信息"};
    sprintf(all_title, "请输入%s名称", title[type-2]);
    gtk_window_set_title(GTK_WINDOW(query_window), all_title);

    //用来传递名字及分辨查询或重头查询的结构体
    struct query_judge *s1,*s2;
    s1 = (struct query_judge *)malloc(sizeof(struct query_judge));
    s2 = (struct query_judge *)malloc(sizeof(struct query_judge));
    s1->flag = 0;
    s2->flag = 1;
    s1->entry = entry;
    s2->entry = entry;

    b_next = gtk_button_new_with_label("查询");
    g_signal_connect(G_OBJECT(b_next),"clicked", G_CALLBACK(query_node[type-2]), s1);//函数指针
    gtk_table_attach(GTK_TABLE(table),b_next, 1, 2, 1, 2,
                     GTK_EXPAND, GTK_EXPAND, 0, 0);
    if(type == 3 || type == 4)
    {
        b_query = gtk_button_new_with_label("从头查询");
        g_signal_connect(G_OBJECT(b_query), "clicked", G_CALLBACK(query_node[type-2]), s2);//函数指针
        gtk_table_attach(GTK_TABLE(table), b_query, 3, 4, 1, 2,
                         GTK_EXPAND, GTK_EXPAND, 0, 0);
    }

    b_cancel = gtk_button_new_with_label("退出");
    g_signal_connect(G_OBJECT(b_cancel), "clicked", G_CALLBACK(f_cancel), query_window);
    gtk_table_attach(GTK_TABLE(table),b_cancel, 5, 6, 1, 2,
                     GTK_EXPAND, GTK_EXPAND, 0, 0);
    gtk_widget_show_all(query_window);
}

////函数名：Statis_info
////功能：弹出一个统计框，由传入参数设置具体内容
////输入参数：title 统计框标题,col1 第一列标题,col2 第二列标题,in 传入的model
////返回值：无
//void Statis_info(char *title,char *col1,char *col2,GtkListStore *in)
//{
//    GtkWidget *statis_window;
//    GtkWidget *b_ok,*b_cancel;
//    GtkWidget *vbox;
//    GtkWidget *hbox;
//    GtkWidget *list;
//    GtkCellRenderer *renderer;
//    GtkTreeViewColumn  *column;
//    GtkWidget *swin;
//
//    statis_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
//    gtk_container_set_border_width (GTK_CONTAINER (statis_window), 0);
//    gtk_window_set_title (GTK_WINDOW (statis_window), title);
//    gtk_window_set_position (GTK_WINDOW (statis_window), GTK_WIN_POS_CENTER);
//    gtk_widget_set_size_request (statis_window, 300, 350);
//
//    list = gtk_tree_view_new();      //创建view等待与传入的model连接
//
//    renderer = gtk_cell_renderer_text_new();
//    column = gtk_tree_view_column_new_with_attributes(col1,
//                                                      renderer, "text", COLUMN, NULL);
//    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
//    column = gtk_tree_view_column_new_with_attributes(col2,
//                                                      renderer, "text", COMMENT, NULL);
//    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
//
//    gtk_tree_view_set_model(GTK_TREE_VIEW (list),
//                            GTK_TREE_MODEL(in));
//
//    vbox = gtk_vbox_new(FALSE, 0);
//    gtk_container_add(GTK_CONTAINER(statis_window), vbox);
//
//    swin = gtk_scrolled_window_new(NULL, NULL);
//    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(swin),
//                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
//    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(swin),
//                                         GTK_SHADOW_ETCHED_IN);
//    gtk_box_pack_start(GTK_BOX(vbox), swin, TRUE, TRUE, 0);
//    gtk_container_add(GTK_CONTAINER (swin), list);
//    hbox=gtk_hbox_new(FALSE,0);
//    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
//    b_cancel=gtk_button_new_with_label("确定");
//    g_signal_connect(G_OBJECT(b_cancel),"clicked",G_CALLBACK(f_cancel),statis_window);
//    gtk_box_pack_start(GTK_BOX(hbox),b_cancel,TRUE,FALSE,0);
//
//    gtk_widget_show_all(statis_window);
//}

/**连接取消按钮关闭当前窗口*/
void f_cancel(GtkWidget *button,GtkWidget *win)
{
    gtk_widget_hide(win);
}

/**********************
 处理选择及节点位置
 ***********************/
//函数名：Judge_NODE_Type
//功能：根据输入iter深度判断节点类型
//输入参数：iter
//返回值：iter深度对应枚举的节点类型
gint Judge_NODE_Type(GtkTreeIter *iter)
{
    GtkTreePath *path;
    GtkTreeModel *model;
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    path= gtk_tree_model_get_path(model, iter);
    return(gtk_tree_path_get_depth (path));
}

/*******************
 显示数据
 *******************/
//函数名：Show_Node
//功能：将选中的节点信息在显示栏中显示出来
//输入参数：iter
//返回值：无
int Show_Node(GtkTreeIter iter)//值传递不影响selectediter
{
    GtkTreeModel *model;
    GtkTreePath *path;

    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    path= gtk_tree_model_get_path(model, &iter);
    char *name;
    gtk_tree_model_get (model,&iter,
                        COLUMN,&name,
                        -1);
    switch(Judge_NODE_Type(&iter))
    {
        case TYPE_ROOT:
            return 1;
        case TYPE_pur:
            liststore=Show_pur(name);
            break;
        case TYPE_sup:
        {
            char *P_name;
            gtk_tree_path_up(path);//获取上一级父节点path
            gtk_tree_model_get_iter(model,&iter,path);//获取上一级父节点iter
            gtk_tree_model_get (model,&iter,
                                COLUMN,&P_name,//获取上一级父节点name
                                -1);
            liststore=Show_sup(name,P_name);
            break;
        }
        case TYPE_trans:
        {
            char *P_name,*PP_name;
            gtk_tree_path_up(path);
            gtk_tree_model_get_iter(model,&iter,path);
            gtk_tree_model_get (model,&iter,
                                COLUMN,&P_name,
                                -1);
            gtk_tree_path_up(path);
            gtk_tree_model_get_iter(model,&iter,path);
            gtk_tree_model_get (model,&iter,
                                COLUMN,&PP_name,
                                -1);
            liststore=Show_trans(name,P_name,PP_name);
            break;
        }
        default :
            return 0;
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(showlist),
                            GTK_TREE_MODEL(liststore));
    return 1;
}

/**对应3个节点显示的3个函数，返回对应GtkListStore*/
GtkListStore *Show_pur(char *name)
{
    PUR_COM *ppur;
    ppur=PUR_search(name);
    char str[20];
    gtk_list_store_set(lstore[0], &pur_iter[0],
                       COMMENT, ppur->pur_num,
                       -1);
    gtk_list_store_set(lstore[0], &pur_iter[1],
                       COMMENT, ppur->pur_name,
                       -1);
    sprintf(str,"%d",ppur->pur_plan_num);
    gtk_list_store_set(lstore[0], &pur_iter[2],
                       COMMENT, str,
                       -1);
    sprintf(str,"%.2f",ppur->pur_plan_money);
    gtk_list_store_set(lstore[0], &pur_iter[3],
                       COMMENT, str,
                       -1);
    sprintf(str,"%d",ppur->pur_month_num);
    gtk_list_store_set(lstore[0], &pur_iter[4],
                       COMMENT, str,
                       -1);
    sprintf(str,"%.2f",ppur->pur_month_money);
    gtk_list_store_set(lstore[0], &pur_iter[5],
                       COMMENT, str,
                       -1);
    sprintf(str,"%d",ppur->pur_total_num);
    gtk_list_store_set(lstore[0], &pur_iter[6],
                       COMMENT, str,
                       -1);
    sprintf(str,"%.2f",ppur->pur_total_money);
    gtk_list_store_set(lstore[0], &pur_iter[7],
                       COMMENT, str,
                       -1);
    return(lstore[0]);
}

GtkListStore *Show_sup(char *name,char *P_name)
{
    PUR_COM *ppur;
    ppur=PUR_search(P_name);
    SUP_COM *psup;
    psup=SUP_search(name,ppur->snext);
    char str[20];
    gtk_list_store_set(lstore[1], &sup_iter[0],
                       COMMENT, psup->pur_num,
                       -1);
    gtk_list_store_set(lstore[1], &sup_iter[1],
                       COMMENT, psup->sup_num,
                       -1);
    gtk_list_store_set(lstore[1], &sup_iter[2],
                       COMMENT, psup->sup_name,
                       -1);
    sprintf(str,"%d",psup->sup_mile);
    gtk_list_store_set(lstore[1], &sup_iter[3],
                       COMMENT, str,
                       -1);
    sprintf(str,"%d",psup->sup_month_num);
    gtk_list_store_set(lstore[1], &sup_iter[4],
                       COMMENT, str,
                       -1);
    sprintf(str,"%.2f",psup->sup_month_money);
    gtk_list_store_set(lstore[1], &sup_iter[5],
                       COMMENT, str,
                       -1);
    sprintf(str,"%d",psup->sup_total_num);
    gtk_list_store_set(lstore[1], &sup_iter[6],
                       COMMENT, str,
                       -1);
    sprintf(str,"%.2f",psup->sup_total_money);
    gtk_list_store_set(lstore[1], &sup_iter[7],
                       COMMENT, str,
                       -1);
    sprintf(str,"%.2f",psup->grade_mine);
    gtk_list_store_set(lstore[1], &sup_iter[8],
                       COMMENT, str,
                       -1);

    return(lstore[1]);
}


GtkListStore *Show_trans(char *name,char *P_name,char *PP_name)
{
    PUR_COM *ppur;
    ppur=PUR_search(PP_name);
    SUP_COM *psup;
    psup=SUP_search(P_name,ppur->snext);
    TRANS *ptrans;
    ptrans=TRANS_search(name,psup->tnext);

    char str[20];
    gtk_list_store_set(lstore[2], &trans_iter[0],
                       COMMENT, ptrans->pur_num,
                       -1);
    gtk_list_store_set(lstore[2], &trans_iter[1],
                       COMMENT, ptrans->sup_num,
                       -1);
    gtk_list_store_set(lstore[2], &trans_iter[2],
                       COMMENT, ptrans->ship_num,
                       -1);
    gtk_list_store_set(lstore[2], &trans_iter[3],
                       COMMENT, ptrans->ship_name,
                       -1);
    sprintf(str,"%d",ptrans->trans_num);
    gtk_list_store_set(lstore[2], &trans_iter[4],
                       COMMENT, str,
                       -1);
    sprintf(str,"%.2f",ptrans->trans_money);
    gtk_list_store_set(lstore[2], &trans_iter[5],
                       COMMENT, str,
                       -1);
    sprintf(str,"%.2f",ptrans->grade_mine);
    gtk_list_store_set(lstore[2], &trans_iter[6],
                       COMMENT, str,
                       -1);
    return(lstore[2]);
}


//函数名：login
//功能：登录验证函数，点击login按钮时调用
//输入参数：
//返回值：无
void login(GtkWidget *widget,gpointer data)
{
    gchar *name;
    gchar *pwd;
    struct login_widget *wgt;
    wgt = (struct loging_widget *)data;
    //获取输入的信息
    name = gtk_entry_get_text(GTK_ENTRY(wgt->entry_username));
    pwd = gtk_entry_get_text(GTK_ENTRY(wgt->entry_pwd));
    if((strcmp(name,NAME) == 0) && (strcmp(pwd,PWD) == 0))
    {
        gtk_label_set_text(GTK_LABEL(wgt->label_tips),"Welcome to AchsMIS");
        gtk_widget_show_all(window);
        gtk_widget_hide(wgt->window);
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(wgt->label_tips),"Invalid user name or password.");
    }
}

//函数名：init_login_widget
//功能：登录框初始化函数
//输入参数：
//返回值：无
void init_login_widget()
{
    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(wgt.window), GTK_WIN_POS_CENTER);
    gtk_window_set_keep_above (GTK_WINDOW(wgt.window),1);
    wgt.label_tips = gtk_label_new("Welcome,please login first");
    wgt.button_login = gtk_button_new_with_label("login");
    wgt.button_exit = gtk_button_new_with_label("exit");
    wgt.entry_username = gtk_entry_new_with_max_length(10);
    wgt.entry_pwd = gtk_entry_new_with_max_length(10);
    wgt.label_username = gtk_label_new("User name :");
    wgt.label_pwd = gtk_label_new("Password :");
    wgt.vbox = gtk_vbox_new(FALSE,20);
    wgt.hbox_username = gtk_hbox_new(FALSE,20);
    wgt.hbox_pwd = gtk_hbox_new(FALSE,20);
    wgt.hbox_button = gtk_hbox_new(FALSE,20);
    //设置窗体
    gtk_window_set_title(GTK_WINDOW(wgt.window),"System login");
    gtk_window_set_resizable(GTK_WINDOW(wgt.window),FALSE);
    //设置布局盒子
    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.label_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.entry_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.label_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.entry_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_button),wgt.button_login,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_button),wgt.button_exit,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.label_tips,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_button,TRUE,FALSE,10);
    //设置密码框不可见，用户输入时显示“*”
    gtk_entry_set_visibility(GTK_ENTRY(wgt.entry_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.entry_pwd),'*');
    g_signal_connect(GTK_OBJECT(wgt.button_login),"clicked",GTK_SIGNAL_FUNC(login),&wgt);
    g_signal_connect(GTK_OBJECT(wgt.window),"destroy",GTK_SIGNAL_FUNC(gtk_win_destroy),NULL);
    g_signal_connect(GTK_OBJECT(wgt.button_exit),"clicked",GTK_SIGNAL_FUNC(gtk_win_destroy),NULL);
    gtk_container_add(GTK_CONTAINER(wgt.window),wgt.vbox);
    gtk_widget_show_all(wgt.window);
}

void gtk_win_destroy(GtkWidget *widget,gpointer data)
{
    gtk_main_quit();
}

/**< 数据文件全局变量*/
char *gp_pur_info_filename="pur.dat";          /*单位信息数据文件*/
char *gp_sup_info_filename="sup.dat";          /*成果信息数据文件*/
char *gp_trans_info_filename="trans.dat";          /*完成人员信息数据文件*/

/**3类节点名称字符串数组*/
char *Node_Str[]=
{
    "采购企业",
    "供货企业",
    "采购运输基本信息"
};

/**3类信息需填资料个数*/
int NODE_INS[]=
{
    0,0,8,9,7
} ;

/**3类信息需填资料字符串数组*/
char *pur_Str[]=
{
    "采购企业编号:",
    "采购企业名称:",
    "计划采购数量:",
    "计划采购金额:",
    "当月采购数量:",
    "当月采购金额:",
    "累积采购数量:",
    "累积采购金额:"
};
char *sup_Str[]=
{
    "采购企业编号:",
    "供货企业编号:",
    "供货企业名称:",
    "海运里程:",
    "当月采购数量:",
    "当月采购金额:",
    "累积采购数量:",
    "累积采购金额:",
    "铁矿石平均品位:"
};
char *trans_Str[]=
{
    "采购企业编号:",
    "供货企业编号:",
    "运输船只编号:",
    "运输船只名称:",
    "运输数量:",
    "价值金额:",
    "矿石品位:"
};

/****************
 新增节点
 ****************/

//函数名：Add_node
//功能：添加3种节点统一函数，由entry_info确定按钮调用
//输入参数：
//返回值：无
void Add_node(GtkWidget *button,struct nodecreate *nodec)
{
    GtkTreeModel *model;
    int error=0;
    char *str;

    switch(nodec->type)
    {
        case 2://插入单位节点
        {
            PUR_COM *pNew,*pSearch;
            pNew = (PUR_COM *)calloc(1, sizeof(PUR_COM));

            //zengjiazaizheli
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
            strcpy(pNew->pur_num,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
            strcpy(pNew->pur_name,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
            pNew->pur_plan_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
            pNew->pur_plan_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
            pNew->pur_month_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
            pNew->pur_month_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
            pNew->pur_total_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[7]));
            pNew-> pur_total_money = atof(str);

            if(gp_head==NULL)
                gp_head=pNew;
            else
            {
                pSearch=gp_head;
                while(pSearch->next!=NULL)
                {
                    pSearch=pSearch->next;
                }
                pSearch->next=pNew;
            }
            gtk_tree_store_append(treestore,&pNew->iter,&rootiter);
            gtk_tree_store_set(treestore,&pNew->iter,
                               COLUMN,pNew->pur_num,
                               -1);
            break;
        }
        case 3://插入科技成果节点
        {
            PUR_COM *ppur;
            SUP_COM *pNew;
            pNew = (SUP_COM *)calloc(1, sizeof(SUP_COM));

            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
            strcpy(pNew->pur_num,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
            strcpy(pNew->sup_num,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
            strcpy(pNew->sup_name,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
            pNew->sup_mile = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
            pNew->sup_month_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
            pNew->sup_month_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
            pNew->sup_total_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[7]));
            pNew->sup_total_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[8]));
            pNew->grade_mine = atof(str);


            if((ppur=insert_SUP(pNew))!=NULL) //使用insert_ACHS函数
            {
                gtk_tree_store_append(treestore,&pNew->iter,&ppur->iter);/*添加条目*/
                gtk_tree_store_set(treestore,&pNew->iter,        /*设置新添加条目的文本显示*/
                                   COLUMN,pNew->sup_num,
                                   -1);
            }
            else
                error=1;
            break;
        }
        case 4://插入完成人员节点
        {
            SUP_COM *psup;
            TRANS *pNew;
            pNew = (TRANS *)calloc(1,sizeof(TRANS));

            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
            strcpy(pNew->pur_num,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
            strcpy(pNew->sup_num,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
            strcpy(pNew->ship_num,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
            strcpy(pNew->ship_name,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
            pNew->trans_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
            pNew->trans_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
            pNew->grade_mine = atof(str);


            if((psup=insert_TRANS(pNew))!=NULL) //使用insert_MEMBER函数
            {
                gtk_tree_store_append(treestore,&pNew->iter,&psup->iter);/*添加条目*/
                gtk_tree_store_set(treestore,&pNew->iter,        /*设置新添加条目的文本显示*/
                                   COLUMN,pNew->ship_num,
                                   -1);
            }
            else
                error=1;
            break;
        }
        default:
            dialog_info("添加失败!");
    }
    printf("%d",error);
    if(error==0)
    {
        model=GTK_TREE_MODEL(treestore);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);//重新连接model和view
        dialog_info("添加成功！");
        gtk_widget_hide(nodec->window);
        free(nodec);
    }
}

//函数名：insert_ACHS
//功能：插入科技成果节点函数，由Add_Node中情况3调用
//输入参数：pNew 指向新节点的指针
//返回值：对应单位节点指针
PUR_COM * insert_SUP(SUP_COM *pNew)
{
    PUR_COM *ppur;
    SUP_COM *pSearch;
    ppur=PUR_search(pNew->pur_num);
    if(ppur==NULL)
        return(ppur);//未找到对应学院则结束函数

    if(ppur->snext==NULL)
        ppur->snext=pNew;
    else
    {
        pSearch=ppur->snext;
        while(pSearch->next!=NULL)
        {
            pSearch=pSearch->next;
        }
        pSearch->next=pNew; //找到后插入到后面
    }
    return(ppur);
}

//函数名：insert_ACHS
//功能：插入完成人员节点函数，由Add_Node中情况4调用
//输入参数：pNew 指向新节点的指针
//返回值：对应科技成果节点指针
SUP_COM *insert_TRANS(TRANS *pNew)
{
    PUR_COM *ppur;
    SUP_COM *psup;
    TRANS *pSearch;

    ppur=PUR_search(pNew->pur_num);
    if(ppur==NULL)
        return(NULL);//未找到对应学院则结束函数

    psup=SUP_search(pNew->sup_num,ppur->snext);
    if(psup==NULL)
        return(NULL);//未找到对应科技成果则结束函数

    if(psup->tnext==NULL)
        psup->tnext=pNew;
    else
    {
        pSearch=psup->tnext;
        while(pSearch->next!=NULL)
        {
            pSearch=pSearch->next;
        }
        pSearch->next=pNew; //找到后插入到后面
    }
    return(psup);
}

/****************
 删除节点
 ****************/
//函数名：Del_Node
//功能：删除3种节点统一函数，由“删除”按钮调用
//输入参数：
//返回值：无
void Del_Node(GtkWidget *button)
{
    GtkWidget *dialog;
    int flag,type,error=0;

    type=Judge_NODE_Type(&selectediter);//判断现在选中节点类型
    if(type==TYPE_ROOT||type==0)
    {
        dialog_info("ROOT节点无法删除！");
        return;
    }
    GtkTreeModel *model;
    GtkTreePath *path;
    GtkTreeIter iter;
    char *name;

    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    path= gtk_tree_model_get_path(model, &selectediter);
    gtk_tree_model_get (model,&selectediter,
                        COLUMN,&name,
                        -1);
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_OK_CANCEL,
                                    "确定删除本节点（及其子节点）？");
    gtk_window_set_title(GTK_WINDOW(dialog), "删除节点");
    flag=gtk_dialog_run(GTK_DIALOG(dialog));
    switch(flag)
    {
        case GTK_RESPONSE_OK:
        {
            switch(type)
            {
                case TYPE_pur:
                    error=Del_pur(name);
                    break;
                case TYPE_sup:
                {
                    char *P_name;
                    gtk_tree_path_up(path);                  //提升path
                    gtk_tree_model_get_iter(model,&iter,path);
                    gtk_tree_model_get (model,&iter,
                                        COLUMN,&P_name,     //得到对应科技成果名称
                                        -1);
                    gtk_tree_view_expand_to_path(GTK_TREE_VIEW(treeview),path);
                    error=Del_sup(name,P_name);
                    break;
                }
                case TYPE_trans:
                {
                    char *P_name;
                    char *PP_name;
                    gtk_tree_path_up(path);
                    gtk_tree_model_get_iter(model,&iter,path);
                    gtk_tree_model_get (model,&iter,
                                        COLUMN,&P_name,
                                        -1);
                    gtk_tree_path_up(path);
                    gtk_tree_model_get_iter(model,&iter,path);
                    gtk_tree_model_get (model,&iter,
                                        COLUMN,&PP_name,
                                        -1);
                    error=Del_trans(name,P_name,PP_name);
                    break;
                }
            }
            break;
        }
        case GTK_RESPONSE_CANCEL:
            gtk_widget_destroy(dialog);
            error=1;
    }
    if(error==0)
        dialog_info("删除成功！");
    gtk_widget_destroy(dialog);
};

//函数名：Del_Dept
//功能：删除单位节点，由Del_Node函数case 2调用
//输入参数：name 单位名称
//返回值：int 1为有错，0为正常
int Del_pur(char *name)
{
    PUR_COM *pSearch,*pPre;
    int flag=1;
    pSearch=gp_head;
    if(!(flag=strcmp(name,pSearch->pur_num)))
    {
        gp_head=gp_head->next;
        gtk_tree_store_remove(treestore,&selectediter);  //删除树状列表对应iter
        return 0;
    }
    do
    {
        pPre=pSearch;
        pSearch=pSearch->next;
        if(pSearch==NULL)
            break;
    }
    while((flag=strcmp(name,pSearch->pur_num)));
    if(!flag)
    {
        pPre->next=pSearch->next;  //讲前一节点直接连至后一节点
        gtk_tree_store_remove(treestore,&selectediter);
        return(0);
    }

    else
    {
        dialog_info("无对应名称单位！");
        return(1);
    }
}

//函数名：Del_Achs
//功能：删除科技成果节点，由Del_Node函数case 3调用
//输入参数：name 科技成果名称，P_name 对应单位名称
//返回值：int 1为有错，0为正常
int Del_sup(char *name,char *P_name)
{
    PUR_COM *ppur;
    TRANS *pSearch,*pPre;

    int flag=1;

    ppur=PUR_search(P_name); //调用DEPT_search函数搜索对应单位名称
    pSearch=ppur->snext;

    if(!(flag=strcmp(name,pSearch->sup_num)))
    {

        ppur->snext=pSearch->next;
        gtk_tree_store_remove(treestore,&selectediter);
        return 0;
    }

    do
    {
        pPre=pSearch;
        pSearch=pSearch->next;
        if(pSearch==NULL)
            break;
    }
    while((flag=strcmp(name,pSearch->sup_num)));

    if(!flag)
    {
        pPre->next=pSearch->next;
        gtk_tree_store_remove(treestore,&selectediter);
        return(0);
    }
    else
    {
        dialog_info("无对应名称科技成果！");
        return(1);
    }
};

//函数名：Del_Member
//功能：删除完成人员节点，由Del_Node函数case 4调用
//输入参数：name 完成人员名称，P_name 对应科技成果名称，PP_name 对应单位名称
//返回值：int 1为有错，0为正常
int Del_trans(char *name,char *P_name,char *PP_name)
{
    PUR_COM *ppur;
    SUP_COM *psup;
    TRANS *pSearch,*pPre;

    int flag=1;

    ppur=PUR_search(PP_name);
    psup=SUP_search(P_name,ppur->snext);
    pSearch=psup->tnext;

    if(!(flag=strcmp(name,pSearch->ship_num)))
    {
        psup->tnext=pSearch->next;
        gtk_tree_store_remove(treestore,&selectediter);
        return 0;
    }
    do
    {
        pPre=pSearch;
        pSearch=pSearch->next;
        if(pSearch==NULL)
            break;
    }
    while((flag=strcmp(name,pSearch->ship_num)));
    if(!flag)
    {
        pPre->next=pSearch->next;
        gtk_tree_store_remove(treestore,&selectediter);
        return(0);
    }
    else
    {
        dialog_info("无对应名称完成人员！");
        return(1);
    }
};
/****************
 编辑节点
 ****************/
//函数名：Edit_Node
//功能：编辑节点
//输入参数：
//返回值：无
void Edit_Node(GtkWidget *button,struct nodecreate *nodec)
{
    char *str;
    GtkTreeIter *iter;
    switch(nodec->type)
    {
        case TYPE_pur:
        {
            PUR_COM *pNew;
            pNew=nodec->unp.pur;
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
            strcpy(pNew->pur_name,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
            pNew->pur_plan_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
            pNew->pur_plan_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
            pNew->pur_month_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
            pNew->pur_month_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
            pNew->pur_total_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[7]));
            pNew->pur_total_money = atof(str);
            break;
        }
        case TYPE_sup:
        {
            SUP_COM *pNew;
            pNew=nodec->unp.sup;

            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
            strcpy(pNew->sup_name,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
            pNew->sup_mile = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
            pNew->sup_month_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
            pNew->sup_month_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
            pNew->sup_total_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[7]));
            pNew->sup_total_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[8]));
            pNew->grade_mine = atof(str);
           break;
        }
        case TYPE_trans:
        {
            TRANS *pNew;
            pNew=nodec->unp.trans;
            iter=&pNew->iter;

        
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
            strcpy(pNew->ship_name,str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
            pNew->trans_num = atoi(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
            pNew->trans_money = atof(str);
            str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
            pNew->grade_mine = atof(str);
            break;
        }
    }
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(treestore));
    gtk_widget_hide(nodec->window);
    Show_Node(selectediter);  //编辑框确定后将数据更新
}




/**************
 查询节点
 **************/

//函数名：Query_Dept
//功能：查询学院
//输入参数：in 包含iter和名称的结构
//返回值：无
void Query_pur(GtkWidget *button,struct query_judge *in)
{
    char *str;
    str=(char*)gtk_entry_get_text(GTK_ENTRY(in->entry));//获取输入框数据
    PUR_COM *ppur;
    ppur=PUR_search(str);
    if(ppur!=NULL)
    {
        expand_select(ppur->iter);
    }
}

//函数名：Query_Achs
//功能：查询科技成果
//输入参数：in 包含iter和名称的结构
//返回值：无
void Query_sup(GtkWidget *button,struct query_judge *in)
{
    char *str;
    str=gtk_entry_get_text(GTK_ENTRY(in->entry));//获取输入框数据static DEPT_NODE *pDept;
    int if_head=in->flag;
    static PUR_COM *ppur; //使用静态变量保证从上一次搜索处开始
    static SUP_COM *psup;
    if(if_head==1||ppur==NULL)//若是由从头查询或到尾再次初始化
        ppur=gp_head;
    int flag=1;
    while(ppur!=NULL)
    {
        if(if_head==1)      //若是查询（继续）不改变，直接从最内层继续搜索
            psup=ppur->snext;
        while(psup!=NULL)
        {
            if(!(flag=strcmp(psup->sup_num,str)))
            {
                expand_select(psup->iter);
                psup=psup->next;
                return;
            }
            psup=psup->next;
        }
        if_head=1;
        ppur=ppur->next;
    }
    if(flag!=0)
    {
        dialog_info("未发现此供货企业！");
    }
}

//函数名：Query_Member
//功能：查询完成人员
//输入参数：in 包含iter和名称的结构
//返回值：无
void Query_trans(GtkWidget *button,struct query_judge *in)
{
    char *str;
    str=gtk_entry_get_text(GTK_ENTRY(in->entry));//获取输入框数据
    int if_head=in->flag;
    static PUR_COM *ppur; //使用静态变量保证从上一次搜索处开始
    static SUP_COM *psup;
    static TRANS *ptrans;
    if(if_head==1||ppur==NULL)//若是由从头查询或到尾再次初始化
        ppur=gp_head;
    int flag=1;
    while(ppur!=NULL)
    {
        if(if_head==1)
            psup=ppur->snext;
        while(psup!=NULL)
        {
            if(if_head==1)
                ptrans=psup->tnext;
            while(ptrans!=NULL)
            {
                if(!(flag=strcmp(ptrans->ship_num,str)))
                {
                    expand_select(ptrans->iter);
                    ptrans=ptrans->next;
                    return;
                }
                ptrans=ptrans->next;
            }
            if_head=1;
            psup=psup->next;
        }
        ppur=ppur->next;
    }
    if(flag!=0)
    {
        dialog_info("未发现此运输基本信息！");
    }
}

//函数名：expand_select
//功能：展开并跳转至指定iter
//输入参数：iter treeview中的一个目标iter
//返回值：无
void expand_select(GtkTreeIter iter)
{
    GtkTreeModel *model;
    GtkTreeSelection *select;
    GtkTreePath *path;
    select = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    path = gtk_tree_model_get_path(model,&iter);
    gtk_tree_view_expand_to_path(GTK_TREE_VIEW(treeview),path);
    gtk_tree_selection_select_iter(select,&iter);
    Show_Node(iter);
}

/**************
 搜索节点
 **************/
/**，返回*/

//函数名：DEPT_search
//功能：按名称搜索单位
//输入参数：D_name 单位名称
//返回值：单位节点指针
PUR_COM *PUR_search(char *P_name)
{
    PUR_COM *pSearch;
    int flag=1;
    pSearch=gp_head;
    while((flag=strcmp(P_name,pSearch->pur_num))&&pSearch->next!=NULL)
    {
        pSearch=pSearch->next;
    }
    if(!flag)
        return(pSearch);
    else
    {
        dialog_info("无对应名称采购企业！");
        return(NULL);
    }
}

//函数名：ACHS_search
//功能：按名称搜索科技成果节点
//输入参数：A_name 科技成果节点名称，ACHS 所在学院头科技成果节点指针
//返回值：科技成果节点节点指针
SUP_COM *SUP_search(char *S_name,SUP_COM *SUP)
{
    SUP_COM *pSearch;
    pSearch=SUP;
    int flag=1;
    while((flag=strcmp(S_name,pSearch->sup_num))&&(pSearch->next)!=NULL)
    {
        pSearch=pSearch->next;
    }
    if(!flag)
        return(pSearch);
    else
    {
        dialog_info("无对应名称供货企业！");
        return(NULL);
    }
}

//函数名：MEMBER_search
//功能：按名称搜索完成人员节点
//输入参数：M_name 完成人员节点名称，ACHS 所属科技成果头完成人员节点指针
//返回值：完成人员节点节点指针
TRANS *TRANS_search(char *T_name,TRANS *Trans)
{
    TRANS *ptrans;
    ptrans=Trans;
    int flag=1;
    while((flag=strcmp(T_name,ptrans->ship_num))&&ptrans->next!=NULL)
    {
        ptrans=ptrans->next;
    }
    if(!flag)
        return(ptrans);
    else
    {
        dialog_info("无对应名称运输企业！");
        return(NULL);
    }
}





/**************
 统计信息
 **************/
//函数名：statis_func1
//功能：统计各单位科技成果数量，调用Statis_info显示统计结果
//输入参数：
//返回值：无
void statis_func1(GtkWidget *button)
{

    PUR_COM *ppur;
    ppur = gp_head;
        int pur_total_nums ;
        float pur_total_moneys ;
        int sup_total_nums ;
        float sup_total_moneys;
 pur_total_nums = 0;
   pur_total_moneys = 0;
    sup_total_nums = 0;
   sup_total_moneys = 0;
    while (ppur != NULL) {
        pur_total_nums += ppur->pur_total_num;
        pur_total_moneys += ppur->pur_total_money;
        SUP_COM *psup = ppur->snext;
        while (psup != NULL) {
            sup_total_nums += psup->sup_total_num;
            sup_total_moneys += psup->sup_total_money;
            psup = psup->next;
        }
        ppur = ppur->next;
    }
    GtkWidget *dialog;
    char str[100];
    char str2[100];
char str3[100];
    char str4[100];
    sprintf(str,"%d",pur_total_nums);
    sprintf(str2,"%.2f",pur_total_moneys);
    sprintf(str3,"%d",sup_total_nums);
    sprintf(str4,"%.2f",sup_total_moneys);
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "所有供货企业总累积采购数量：\n%s\n所有供货企业总累积采购金额：\n%s\n所有供货企业总累积采购数量：\n%s\n所有供货企业总累积采购金额：\n%s",str,
                                    str2,str3,str4);
    gtk_window_set_title(GTK_WINDOW(dialog), "累积采购数量及金额");
    gtk_window_set_keep_above (GTK_WINDOW(dialog),1);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);




}

//函数名：statis_func2
//功能：统计各单位完成人员成果排名，调用Statis_info显示统计结果
//输入参数：
//返回值：无
void statis_func2(GtkWidget *button)
{
    PUR_COM *ppur;
    ppur = gp_head;
    int ship_num = 0;
    float ship_money = 0;
    while (ppur != NULL) {
        SUP_COM *psup = ppur->snext;
        while (psup != NULL) {
            TRANS *ptrans = psup->tnext;
            while (ptrans != NULL) {
                ship_num += ptrans->trans_num;
                ship_money += ptrans->trans_money;
                ptrans = ptrans->next;
            }
            psup = psup->next;
        }
        ppur = ppur->next;
    }
    GtkWidget *dialog;
    char str[100];
    char str2[100];
    
    sprintf(str,"%d",ship_num);
    sprintf(str2,"%.2f",ship_money);
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "运输船只总运输数量：\n%s\n运输船只总运输金额：\n%s",str,
                                    str2);
    gtk_window_set_title(GTK_WINDOW(dialog), "运输船只总运输数量及金额");
    gtk_window_set_keep_above (GTK_WINDOW(dialog),1);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);}

//函数名：statis_func3
//功能：统计所有50岁以下第一完成人，调用Statis_info显示统计结果
//输入参数：
//返回值：无
void statis_func3(GtkWidget *button)
{
    PUR_COM *ppur;
    ppur = gp_head;
    int count = 0;
    while (ppur != NULL) {
        SUP_COM *psup = ppur->snext;
        while (psup != NULL) {
            count += 1;
            psup = psup->next;
        }
        ppur = ppur->next;
    
    }
    GtkWidget *dialog;
    char str[100];
    sprintf(str,"%d",count);
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "供货企业总数目：%s",str);
    gtk_window_set_title(GTK_WINDOW(dialog), "供货企业总数目");
    gtk_window_set_keep_above (GTK_WINDOW(dialog),1);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

}




