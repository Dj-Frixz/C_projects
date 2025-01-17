/*
    Testo dell'esercizio:
        Progettare una macchina di turing che, data in ingresso 
        una sequenza di simobli 'A', sostituisca quelli in posto
        dispari con i simboli 'B'

    ANSI escape codes 
    ESC[{line};{column}H moves cursor to line #, column #
    ESC[0K	clears from cursor to end of line
    ESC is \033

*/
#include <stdio.h>
#include <string.h>
#include <time.h>

void custom_delay(int time_in_milliseconds){
    double delay_time = (double)time_in_milliseconds/1000;
    double timediff = 0;
    clock_t curr_time;
    curr_time = clock();
    while(timediff<delay_time){
        timediff = ((double)clock()/CLOCKS_PER_SEC)-((double)curr_time/CLOCKS_PER_SEC);
    }  
}

void print_string(char input_string[]){
    putchar('|');
    for(int i = 0;i<strlen(input_string);i++){
        putchar(input_string[i]);
        putchar('|');
    }
    //putchar('\n');
}

int main(){
    char states[3][2] = {"q0","q1","q2"};
    int num_states = 3;
    char work_alphabet[3] = {'A','B','-'};
    int num_symbols = 3;
    //rows are states, columns are input values
    //dims are, states,inputs and 3 are: value to print, nextstate and direction to move
    int trans_func[3][3][3]={
        {{'A',1,'>'},{'-','-','-'},{'-',2,'-'}},            //q0, A B -
        {{'B',0,'>'},{'-','-','-'},{'-',2,'-'}},            //q1
        {{'-','-','-'},{'-','-','-'},{'-','-','-'}},        //q2
    };


    char input_string[100] = "-AAAAAAAAAA-";
    int cursor_pos = 1;                         //start on first valid letter
    int curr_state = 0;                         //start with first state
    int final_state = 2;
    printf("\e[1;1H\e[2J");                     //clear canvas
    printf("%s",input_string);                  //print first time             
    printf("\ncurr state: %s",states[curr_state]);                  
    while(curr_state != final_state){        
        char curr_char = input_string[cursor_pos];
        int curr_symbol;
        for(int i = 0; i < num_symbols;i++){     //find index of current input
            if(work_alphabet[i]==curr_char){
                curr_symbol = i;
                break;
            }
        }
        char next_char = trans_func[curr_state][curr_symbol][0];
        int next_state = trans_func[curr_state][curr_symbol][1];
        char direction = trans_func[curr_state][curr_symbol][2];
        curr_state = next_state;                //update state 
        input_string[cursor_pos] = next_char;   //update input string 
        printf("\033[1;%dH",cursor_pos+1);        //move cursor to cursor pos to update string
        putchar(next_char);                     //print new value

        switch(direction){
            case '>':
                cursor_pos++;
                break;
            case '<':
                cursor_pos--;
                break;
            case '-':
                //cursor doesn't move
                break;
        }
        printf("\033[2;13H");                    //move to update current state
        printf("\033[0J");                       //clear from cursor to end of line
        printf("%s",states[curr_state]);
        printf("\033[2;%dH",13+strlen(states[curr_state]));     //move to after newly printed state
        printf("\033[0J");                       //clear from cursor to end of line
        custom_delay(1000);
    }
    printf("\nfinished!");
/*
    custom_delay(1000);
    printf("\e[1;1H\e[2J");     //regex clear terminal
    printf("second message");
*/
    return 0;
}

