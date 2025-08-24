#include <stdio.h>
struct bill {
    float total_quantity ;
    float unit_Price ;
};

int main() {
    struct bill paratha ;
    struct bill vegetable ;
    struct bill mineralWater ;

    printf("Quantity Of Paratha: ") ;
    scanf("%f",  &paratha.total_quantity) ;  

    printf("Unit Price: ") ;
    scanf("%f",  &paratha.unit_Price) ;  // paratha


    printf("Quantity Of Vegetables: ") ;
    scanf("%f",  &vegetable.total_quantity) ;

    printf("Unit Price: ") ;
    scanf("%f",  &vegetable.unit_Price) ;   // vegetable


    printf("Quantity Of Mineral Water: ") ;
    scanf("%f",  &mineralWater.total_quantity) ;

    printf("Unit Price: ") ;
    scanf("%f",  &mineralWater.unit_Price) ;  // water 

    int total_people ;
    printf("Number of People: ") ;
    scanf("%d", &total_people) ;
    float payment = (mineralWater.unit_Price * mineralWater.total_quantity ) + (vegetable.unit_Price * vegetable.total_quantity ) + (paratha.unit_Price * paratha.total_quantity ) ;
    float payment_per_person = (payment / total_people) ; 
    printf("\nOutput:\n") ;
    printf("Individual people will pay: %f tk\n", payment_per_person) ;
}

