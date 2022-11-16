/* Name: ENCM 511 App Project 1 
 * File:   UART2.h
 * Author: Nicola Primomo & Kun Lu
 *
 * Created on November 16 , 2022
 */
#ifndef UART2H
#define UART2H

void InitUART2(void) ;
void XmitUART2(char CharNum, unsigned int repeatNo);
void Disp2String(char *str) ;
void Disp2Dec(unsigned int DispNum);
#endif