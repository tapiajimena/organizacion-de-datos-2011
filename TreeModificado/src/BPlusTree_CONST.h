/*
 * BPlusTree_CONST.h
 *
 *  Created on: Apr 22, 2010
 *      Author: juane
 */

#ifndef BPLUSTREE_CONST_H_
#define BPLUSTREE_CONST_H_

/* Constantes de tamaño */

#define BLOCKSIZE			256
#define MAX_PERCENTAGE 		0.8
#define MIN_PERCENTAGE 		0.5
#define MAX_RECORD_PERCENTAGE 	0.25


/* Constantes de estados de nodo */
#define OVERFLOWDED 			99
#define UNDERFLOWDED 			-99

/* Constantes de identificadores inválidos */
#define INVALID_NODE_ID 		-1
#define INVALID_KEY_ID 			-1

/* Constantes de registros en nodos */
#define DUPLICATED				-1
#define NOT_FOUNDED				-2

#define MAX_SIZE_UINT32	4294967295

#endif /* BPLUSTREE_CONST_H_ */
