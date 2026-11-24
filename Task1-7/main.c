/* ==================== Q1.c ==================== */
#include <stdio.h>
int main(void) {
    int price, qty, senior;
    printf("Enter unit price, quantity and senior (1=yes, 0=no): ");
    if (scanf("%d%d%d", &price, &qty, &senior) != 3) return 1;
    int total = price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;
    int net = total > 1000 ? total - 50 : total;
    int gross = price * qty;
    int discount = senior ? gross * 15 / 100 : 0;
    int tax = gross * 5 / 100;
    int correct_total = gross - discount + tax;
    int correct_net = correct_total > 1000 ? correct_total - 50 : correct_total;
    printf("\\nGiven expression: total = %d, net = %d\\n", total, net);
    printf("Correct calculation: gross = %d, discount = %d, tax = %d\\n", gross, discount, tax);
    printf("Correct total = %d, net = %d\\n", correct_total, correct_net);
    puts("Note: count = count++ + 1 has undefined behaviour; do not execute it.");
    return 0;
}

/* ==================== Q2.c ==================== */
#include <stdio.h>
int calls = 0;
int verify_disability_card(int card) { calls++; return card; }
int main(void) {
    int seniors = 0, eligible = 0, cards = 0;
    for (int i = 0; i < 1000; i++) {
        int senior = (i % 2 == 0);
        int class_ok = (i % 4 == 0);
        int card = (i % 10 == 0);
        if ((senior && class_ok) || verify_disability_card(card)) seniors++;
        if (verify_disability_card(card) || (senior && class_ok)) eligible++;
    }
    printf("Passengers tested: 1000\\n");
    printf("Calls when concession condition is checked first: %d\\n", calls);
    calls = 0;
    for (int i = 0; i < 1000; i++) {
        int senior = (i % 2 == 0), class_ok = (i % 4 == 0), card = (i % 10 == 0);
        if ((senior && class_ok) | verify_disability_card(card)) { /* bitwise OR evaluates both */ }
    }
    printf("Calls using bitwise |: %d\\n", calls);
    puts("&& and || short-circuit; & and | evaluate both operands.");
    return 0;
}

/* ==================== Q3.c ==================== */
#include <stdio.h>
enum { LIGHT=0, FAN=1, AC=2, HEATER=3, PUMP=4 };
unsigned char switch_on(unsigned char reg, int dev) { return (unsigned char)(reg | (1u << dev)); }
unsigned char switch_off(unsigned char reg, int dev) { return (unsigned char)(reg & ~(1u << dev)); }
unsigned char toggle(unsigned char reg, int dev) { return (unsigned char)(reg ^ (1u << dev)); }
int is_on(unsigned char reg, int dev) { return (reg & (1u << dev)) != 0; }
void show(unsigned char reg) {
    for (int bit=7; bit>=0; bit--) putchar(((reg >> bit) & 1u) ? '1' : '0');
    putchar('\\n');
}
int main(void) {
    unsigned char reg=0;
    reg=switch_on(reg,LIGHT); printf("After LIGHT ON: "); show(reg);
    reg=switch_on(reg,AC); printf("After AC ON: "); show(reg);
    reg=toggle(reg,FAN); printf("After FAN toggle: "); show(reg);
    reg=switch_off(reg,LIGHT); printf("After LIGHT OFF: "); show(reg);
    printf("AC is %s, PUMP is %s\\n", is_on(reg,AC)?"ON":"OFF", is_on(reg,PUMP)?"ON":"OFF");
    return 0;
}

/* ==================== Q4.c ==================== */
#include <stdio.h>
char grade(int marks) {
    if (marks < 0 || marks > 100) return '?';
    switch (marks / 10) {
        case 10: case 9: return 'S';
        case 8: return 'A';
        case 7: return 'B';
        case 6: return 'C';
        case 5: return 'D';
        default: return 'F';
    }
}
int main(void) {
    int marks[] = {100,95,83,50,49,-5};
    for (int i=0;i<6;i++) printf("%d:%c ", marks[i], grade(marks[i]));
    printf("\\n");
    int tests[] = {100,90,89,80,79,70,69,60,59,50,49,0,-1,101};
    puts("Boundary tests:");
    for (int i=0;i<14;i++) printf("%d:%c ",tests[i],grade(tests[i]));
    puts("");
    return 0;
}

/* ==================== Q5.c ==================== */
#include <stdio.h>
unsigned long checks=0;
int is_prime(unsigned long n) {
    checks=0;
    if (n<2) return 0;
    for (unsigned long i=2; i*i<=n; i++) {
        checks++;
        if (n%i==0) return 0;
    }
    return 1;
}
int main(void) {
    unsigned long tickets[]={97,100,7919,1000003};
    for (int k=0;k<4;k++) {
        int p=is_prime(tickets[k]);
        printf("%8lu %-9s divisions = %lu\\n",tickets[k],p?"prime":"not prime",checks);
    }
    return 0;
}

/* ==================== Q6.c ==================== */
#include <stdio.h>
int main(void) {
    double balance=10000.0, rate=0.02, repayment=2000.0, total_interest=0.0;
    int month=0, limit=360;
    puts("Month   Opening     Interest   Payment    Closing");
    while (balance > 0.005 && month < limit) {
        double opening=balance;
        double interest=opening*rate;
        balance=opening+interest;
        total_interest+=interest;
        double payment=(balance < repayment) ? balance : repayment;
        balance-=payment;
        if (balance < 0.005) balance=0.0;
        month++;
        printf("%5d %10.2f %10.2f %10.2f %10.2f\\n",month,opening,interest,payment,balance);
        if (repayment <= opening*rate) {
            puts("Warning: repayment does not exceed monthly interest; loan will not decrease.");
            break;
        }
    }
    if (balance==0.0) printf("Loan repaid in %d months. Total interest = Rs %.2f\\n",month,total_interest);
    else printf("Safety limit/termination condition reached. Outstanding = Rs %.2f\\n",balance);
    return 0;
}

/* ==================== Q7.c ==================== */
#include <stdio.h>
unsigned long basic_checks, improved_checks;
int prime_basic(unsigned long n) {
    basic_checks=0;
    if(n<2) return 0;
    for(unsigned long i=2;i<n;i++){ basic_checks++; if(n%i==0)return 0; }
    return 1;
}
int prime_improved(unsigned long n) {
    improved_checks=0;
    if(n<2)return 0;
    if(n==2)return 1;
    if(n%2==0){ improved_checks++; return 0; }
    for(unsigned long i=3;i<=n/i;i+=2) {
        improved_checks++;
        if(n%i==0)return 0;
    }
    return 1;
}
int main(void) {
    unsigned long values[]={97,100,7919,1000003};
    puts("Number    Basic result/checks       Redesigned result/checks");
    for(int k=0;k<4;k++) {
        int a=prime_basic(values[k]); unsigned long ca=basic_checks;
        int b=prime_improved(values[k]); unsigned long cb=improved_checks;
        printf("%-9lu %-5s / %-10lu %-5s / %lu\\n",values[k],a?"prime":"composite",ca,b?"prime":"composite",cb);
    }
    puts("Redesign: handle 2 separately and test only odd divisors up to sqrt(n).");
    return 0;
}
