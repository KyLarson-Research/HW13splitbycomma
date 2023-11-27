#include<stdio.h>
#include <string.h>
#include<ctype.h>
#define MAX_LEN 50
int parse_comma_separated_name(char *s, int *comma_loc){
   int i, n=strlen(s);
   for(i=0; i<n; i++){
      if(!( (s[i]>=65&&s[i]<=90) || (s[i]>=97&&s[i]<=122)) ){//find the next alpha
         *comma_loc = i;
         while(!( (s[i]>=65&&s[i]<=90) || (s[i]>=97&&s[i]<=122)) ){// means s_i is not alphanumeric
            i++;
         }
         break;
      }
   }
   return i;
}
void remove_non_alpha(char *s){
   int i, n=strlen(s), j, num_spaces=0;
   char temp;
   for(i=0; i<n; i++){
      if(s[i] == ' ' || s[i] == '\n'){
         num_spaces++;
         for(j=i; j<n; j++){//move the space to the end of the string
            temp = s[j];
            s[j] = s[j+1];
            s[j+1] = temp;
         }
      }
   }
   s[n - num_spaces] = '\0';
   return;
}
void parse(char *buf, int *l, int *c, char *first, char *last){
   *l = parse_comma_separated_name(buf, c);
   strcpy(first, &buf[*l]);
   remove_non_alpha(first);
   strncpy(last, buf, *c);
   remove_non_alpha(last);
   //if(strchr(buf, ',')!=NULL){
   //  printf("%s, %s\n", last, first);
   //}
   return;
}

int main(void) {
   
   char first[MAX_LEN], last[MAX_LEN];
   char buf[MAX_LEN]="";
   int i_l, i_c;
   while(strcmp(buf, "q\n")!=0){
      
      printf("Enter input string:\n");
      fgets(buf, MAX_LEN, stdin);
      if(strcmp(buf, "q\n")==0){break;}
      parse(buf, &i_l, &i_c, first, last);
      while(strchr(buf, ',')==NULL){
         printf("Error: No comma in string.\n\n");
         printf("Enter input string:\n");
         fgets(buf, 100, stdin);
         if(strcmp(buf,"q\n")==0){break;}
         parse(buf, &i_l, &i_c, first, last);
      }
      printf("First word: %s\n", last);
      printf("Second word: %s\n\n", first);
      
   }
   return 0;
}
