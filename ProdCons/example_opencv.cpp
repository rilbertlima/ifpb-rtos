#include <iostream> // for standard I/O
#include <string> // for strings
#include <iomanip> // for controlling float print precision
#include <sstream> // string to number conversion
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>



int max;
int frame_init, frame_end;
std::string image_path = "imagens/3840_RIGHT_0";
/*TODO: criar uma struct para conter além da imagem (tipo cv::Ptr<cv::Mat>), o número do frame 
para que os consumidores possam salvar a imagem de saída com a mesma numeração*/
cv::Ptr<cv::Mat> *buffer;

int use  = 0;
int fill = 0;


#define CMAX (10)
int consumers = 1;

typedef struct __zem_t {
    int value;
    pthread_cond_t  cond;
    pthread_mutex_t lock;
} zem_t;

void zem_init(zem_t *z, int value) {
    z->value = value;
    pthread_cond_init(&z->cond, NULL);
    pthread_mutex_init(&z->lock, NULL);
}

void zem_wait(zem_t *z) {
    pthread_mutex_lock(&z->lock);
    while (z->value <= 0)
        pthread_cond_wait(&z->cond, &z->lock);
    z->value--;
    pthread_mutex_unlock(&z->lock);
}

void zem_post(zem_t *z) {
    pthread_mutex_lock(&z->lock);
    z->value++;
    pthread_cond_signal(&z->cond);
    pthread_mutex_unlock(&z->lock);
}

zem_t empty;
zem_t full;
pthread_mutex_t mutex;

void do_fill(cv::Ptr<cv::Mat> value) {
    buffer[fill] = value;
    fill++;
    if (fill == max)
       fill = 0;
}

cv::Ptr<cv::Mat> do_get() {
    cv::Ptr<cv::Mat> tmp = buffer[use];
    use++;
    if (use == max)
       use = 0;
    return tmp;
}

void *producer(void *arg) {
    int i;

    for (i = frame_init; i <= frame_end; i++) {
        std::string image_path_final = image_path+std::to_string(i)+".tif";
        std::cout << image_path_final << std::endl;

        cv::Ptr<cv::Mat> img = cv::makePtr<cv::Mat>(cv::imread(image_path_final, cv::IMREAD_COLOR));
        printf("Incluindo imagem %d...\n",i);
        zem_wait(&empty);
        pthread_mutex_lock(&mutex);
        do_fill(img);
        pthread_mutex_unlock(&mutex);
        zem_post(&full);
    }

    // end case
    for (i = 0; i < consumers; i++) {
        zem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("Incluindo valor %d...\n",-1);
        do_fill(NULL);
        pthread_mutex_unlock(&mutex);
        zem_post(&full);
    }
    
    return NULL;
}
                                                                               
void *consumer(void *arg) {
    cv::Ptr<cv::Mat> tmp;
    int i=0;
    //TODO: corrigir um erro que pode estar afetando o desempenho
    while(true) {
        zem_wait(&full);
        pthread_mutex_lock(&mutex);
        tmp = do_get();
        
        if (tmp == NULL) {
            pthread_mutex_unlock(&mutex);
            zem_post(&empty);
            break;
        }
        blur(*tmp,*tmp,cv::Size(20,20));
        //TODO: obter a numeração da struct e salvar a imagem de saída com o formato out_<numeroframe>.tif
        std::string path_out = "imagens/out_";
        path_out += std::to_string((long long int) arg)+"_"+std::to_string(i++)+".tif";
        imwrite(path_out, *tmp);
        pthread_mutex_unlock(&mutex);
        zem_post(&empty);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
       fprintf(stderr, "usage: %s <buffersize> <frame_init> <frame_end> <consumers>\n", argv[0]);
       exit(1);
    }
    max   = atoi(argv[1]);
    frame_init = atoi(argv[2]);
    frame_end = atoi(argv[3]);
    consumers = atoi(argv[4]);

    buffer = (cv::Ptr<cv::Mat>*) malloc(max * sizeof(cv::Ptr<cv::Mat>));
    assert(buffer != NULL);
    int i;
    for (i = 0; i < max; i++) {
       buffer[i] = NULL;
    }

    zem_init(&empty,  max); // max are empty 
    zem_init(&full,  0);    // 0 are full
    pthread_mutex_init(&mutex, NULL);

    pthread_t pid, cid[CMAX];
    pthread_create(&pid, NULL, producer, NULL); 
    for (i = 0; i < consumers; i++) {
       pthread_create(&cid[i], NULL, consumer, (void *) (long long int) i); 
    }
    pthread_join(pid, NULL); 
    for (i = 0; i < consumers; i++) {
       pthread_join(cid[i], NULL); 
    }
    return 0;
}
