#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

//apparently strings need a '\0' at the end in C

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};
struct document get_document(char* text) {
    int sen_c=0, par_c=1, wor_c=0;
    int i=0, j=0, x=0, o=0, t=0;
    struct document document;
    
      //nr paragrafe 
    for(i=0;i<strlen(text);i++)
        if(text[i]==10)
        par_c++;
    
    document.paragraph_count=par_c;
  
       //alocare      
    document.data=(struct paragraph*)malloc(document.paragraph_count*sizeof(struct paragraph));
    for(int i=0;i<par_c;i++)
    document.data[i].data=(struct sentence*)malloc(100*sizeof(struct sentence));
    for(int i=0;i<par_c;i++)
    for(int j=0;j<100;j++)
    document.data[i].data[j].data=(struct word*)malloc(100*sizeof(struct word));
    for(int i=0;i<par_c;i++)
    for(int j=0;j<100;j++)
    for(int o=0;o<100;o++)
    document.data[i].data[j].data[o].data=(char*)malloc(100*sizeof(char));
    
    
    //nr enunturi per paragraf
    for(int i=0;i<document.paragraph_count;i++)
    {
        sen_c=0;
        while(text[j]!=10&&j<strlen(text))
        {
            if(text[j]==46)
            sen_c++;
            j++;
        }
        document.data[i].sentence_count=sen_c;
        if(text[j]==10)
        j++;
    }
    //nr cuvinte per enunt    
    j=0;
    for(int i=0;i<document.paragraph_count;i++)
    {
        o=0;
        while(o!=document.data[i].sentence_count)
        {
            wor_c=0;
            while(text[j]!=46&&j<strlen(text))
            {
                if(text[j]==32)
                wor_c++;
                j++;
            }
        document.data[i].data[o].word_count=wor_c+1;
        if(text[j]==46)
        j++;
        o++;
        }
   }
    
    //eliminare endline din text(optional cred)
    t=0;
    for(int i=j=0;i<strlen(text);i++)
    {
        if(text[i]!='\n')
        text[j++]=text[i];
    }
    text[j]='\0';
    
    //incarcare document
    for(int i=0;i<document.paragraph_count;i++)
    {
        o=0;//par
        while(o!=document.data[i].sentence_count)
        {
            //sen
            j=0;
            while(j!=document.data[i].data[o].word_count)
            {
                //word
                x=0;
                while(text[t]>=65&&text[t]<=122)
                {
                //carac din word
                document.data[i].data[o].data[j].data[x]=text[t];
                x++;
                t++;
                }
                if(text[t]=='.'||text[t]==' '||text[t]=='\0')
                {
                t++;
                }
                document.data[i].data[o].data[j].data[x]='\0';
                j++;
                
                document.data[i].data[o].data[j].data=(char*)realloc(document.data[i].data[o].data[j].data,x);
            }
            o++;
        }
    }
    return document;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m-1].data[k-1];

}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k-1];
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
    
    return 0;
}
