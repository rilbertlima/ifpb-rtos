#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
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
#include <sys/time.h>
#include <semaphore.h>

int max;
int frame_init, frame_end;

typedef struct {
  std::string image_path;
  std::string imageNumber;
} imageParameters;

imageParameters imgPasta = {"imagens/3840_RIGHT_0",""};

cv::Ptr<cv::Mat> *buffer;

int use  = 0;
int fill = 0;

#define CMAX (10)
int consumers = 1;

/*
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
*/

sem_t empty;
sem_t full;

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
        std::string image_path_final = imgPasta.image_path+std::to_string(i)+".tif";
        imgPasta.imageNumber = std::to_string(i);
        
        std::ifstream file;
        file.open(image_path_final);
        if (!file) {
          std::cout << "O arquivo: " << image_path_final << " nao existe." << std::endl;
          continue;
        }

        cv::Ptr<cv::Mat> img = cv::makePtr<cv::Mat>(cv::imread(image_path_final, cv::IMREAD_COLOR));
        printf("Incluindo imagem %d...\n",i);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        do_fill(img);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    // end case
    for (i = 0; i < consumers; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("Incluindo valor %d...\n",-1);
        do_fill(NULL);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    
    return NULL;
}
                                                                               
void *consumer(void *arg) {
    cv::Ptr<cv::Mat> tmp;
    int i=0;
    //TODO: corrigir um erro que pode estar afetando o desempenho
    //O bloqueio do pthread_mutex_unlock estava sendo ativo muito tardiamente (após a geracao da imagem)
    //Foi realizado o adiantiamento dessa função para após a obtenção do tmp (imagem)
    while(true) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        tmp = do_get();
        
        pthread_mutex_unlock(&mutex);
        //sem_post(&empty);

        if (tmp == NULL) {
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
            break;
        }
        
        blur(*tmp,*tmp,cv::Size(20,20));
        std::string path_out = "imagens/out_";
        path_out += imgPasta.imageNumber+".tif";
        imwrite(path_out, *tmp);
        //pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

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

    sem_init(&empty, 0,  max); // max are empty 
    sem_init(&full, 0, 0);    // 0 are full
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

    gettimeofday(&tv2, NULL);

    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

    return 0;
}
