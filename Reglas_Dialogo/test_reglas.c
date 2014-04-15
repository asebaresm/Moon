/* 
 * File:   main.c
 * Author: Arave
 *
 * Created on 14 de abril de 2014, 20:20
 */

#include "Reglas_dialogo.h"
#include <assert.h>
#include <time.h>

int main(int argc, char** argv) {
    
    /*Variables para la prueba del modulo*/
    DialogueRules *dr = NULL;
    
    /*Topic ids:*/
    Id tid_1=110, tid_2=120, tid_3=130, tid_4=140, tid_5=NO_ID;
    
    /*Rule ids:*/
    Id rid_1=10, rid_2=20, rid_3=30, rid_4=40, rid_5=50;
    
    /*Variables para prueba de "search_rule_and_pattern": */
    int *pind_patr = NULL;
    int ind_patr;
    char txt_ent[WORD_SIZE]="MOVER NORTE JUGADOR";
    
    /*Topic names:*/
    char tname1[WORD_SIZE]="T_MOVER_N";
    char tname2[WORD_SIZE]="T_MOVER_S";
    char tname3[WORD_SIZE]="T_MOVER_E";
    char tname4[WORD_SIZE]="T_MOVER_O";
    char tname5[WORD_SIZE]="T_MOVER_UP";
    
    /*Patterns for rid_1:*/
    char pttrn1[WORD_SIZE]="MOVER NORTE";
    char pttrn2[WORD_SIZE]="MOVER AL NORTE";
    char pttrn3[WORD_SIZE]="IR NORTE";
    char pttrn4[WORD_SIZE]="IR AL NORTE";
    char pttrn5[WORD_SIZE]="AVANZAR NORTE";
    
    /*Templates for rid_1:*/
    char tmpl1[WORD_SIZE]="Te diriges hacia el norte";
    char tmpl2[WORD_SIZE]="Continuas hacia el norte";
    char tmpl3[WORD_SIZE]="Caminas hacia el norte";
    char tmpl4[WORD_SIZE]="Te mueves a la sala que hay al norte";
    
    /*Inicializamos el seed para la funcion de plantilla aleatoria*/
    srand(time(NULL));
    /*P1*/
    printf("\nPasando prueba 1: ");
    assert((dr = create_dialog()) != NULL);
    printf("OK");
    
     /*P2*/
    printf("\nPasando prueba 2: ");
    assert( 110 == dialog_add_topic(dr, tname1, tid_1));
    assert( 120 == dialog_add_topic(dr, tname2, tid_2));
    assert( 130 == dialog_add_topic(dr, tname3, tid_3));
    assert( 140 == dialog_add_topic(dr, tname4, tid_4));
    assert( NO_ID == dialog_add_topic(dr, tname5, tid_5));
    printf("OK");
    
    /*P3*/
    printf("\nPasando prueba 3: ");
    assert(10 == dialog_add_rule(dr, rid_1));
    assert(20 == dialog_add_rule(dr, rid_2));
    assert(30 == dialog_add_rule(dr, rid_3));
    assert(40 == dialog_add_rule(dr, rid_4));
    assert(50 == dialog_add_rule(dr, rid_5));
    printf("OK");
    
    /*P4*/
    printf("\nPasando prueba 4: ");
    assert(OK == dialog_add_pattern(dr, rid_5, pttrn1));
    assert(OK == dialog_add_pattern(dr, rid_5, pttrn2));
    assert(OK == dialog_add_pattern(dr, rid_5, pttrn3));
    assert(OK == dialog_add_pattern(dr, rid_5, pttrn4));
    assert(OK == dialog_add_pattern(dr, rid_5, pttrn5));
    printf("OK");
    
    /*P5*/
    printf("\nPasando prueba 5: ");
    assert(OK == dialog_add_output_templ(dr, rid_5, tmpl1));
    assert(OK == dialog_add_output_templ(dr, rid_5, tmpl2));
    assert(OK == dialog_add_output_templ(dr, rid_5, tmpl3));
    assert(OK == dialog_add_output_templ(dr, rid_5, tmpl4));
    printf("OK");
    
    /*P6*/
    printf("\nPasando prueba 6: ");
    assert(OK == dialog_add_ruleid_to_topic(dr, tid_1, rid_5));
    printf("OK");
    
    /*P7*/
    printf("\nPasando prueba 7: (Plantillas secuenciales)");
    printf("\nPlantilla 1: %s", select_output_template(dr, rid_5));
    printf("\nPlantilla 2: %s", select_output_template(dr, rid_5));
    printf("\nPlantilla 3: %s", select_output_template(dr, rid_5));
    printf("\nPlantilla 4: %s", select_output_template(dr, rid_5));
    printf("\nPlantilla 5: %s", select_output_template(dr, rid_5));
    printf("\nOK");
    
    /*P8*/
    printf("\nPasando prueba 8: (Plantillas aleatorias)");
    printf("\nPlantilla 1: %s", select_random_output_template(dr, rid_5));
    printf("\nPlantilla 2: %s", select_random_output_template(dr, rid_5));
    printf("\nPlantilla 3: %s", select_random_output_template(dr, rid_5));
    printf("\nPlantilla 4: %s", select_random_output_template(dr, rid_5));
    printf("\nPlantilla 5: %s", select_random_output_template(dr, rid_5));
    printf("\nOK");
    
    /*P9*/
    printf("\nPasando prueba 9: ");
    pind_patr = &ind_patr;
    assert( 50 == search_rule_and_pattern (dr, pind_patr, tid_1, txt_ent));
    assert( ind_patr == 0);
    printf("OK");
    
    destroy_dialog(dr);
    
    printf("\n");
    return (EXIT_SUCCESS);
}

