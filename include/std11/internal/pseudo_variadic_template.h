/*
 * pseudo_variadic_template.h
 *
 *  Created on: 2014/07/07
 *      Author: Haruki Nakayama
 */

#ifndef STDBP_STD11_INTERNAL_PSEUDO_VARIADIC_TEMPLATE_H_
#define STDBP_STD11_INTERNAL_PSEUDO_VARIADIC_TEMPLATE_H_

#define STDBP_STD11_TEMPLATE_PARAMS_1  typename A0
#define STDBP_STD11_TEMPLATE_PARAMS_2  typename A0, typename A1
#define STDBP_STD11_TEMPLATE_PARAMS_3  typename A0, typename A1, typename A2
#define STDBP_STD11_TEMPLATE_PARAMS_4  typename A0, typename A1, typename A2, typename A3
#define STDBP_STD11_TEMPLATE_PARAMS_5  typename A0, typename A1, typename A2, typename A3, typename A4
#define STDBP_STD11_TEMPLATE_PARAMS_6  typename A0, typename A1, typename A2, typename A3, typename A4, typename A5
#define STDBP_STD11_TEMPLATE_PARAMS_7  typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6
#define STDBP_STD11_TEMPLATE_PARAMS_8  typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7
#define STDBP_STD11_TEMPLATE_PARAMS_9  typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8
#define STDBP_STD11_TEMPLATE_PARAMS_10 typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9

#define STDBP_STD11_TEMPLATE_TYPENAMES_1  typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_2  typename, typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_3  typename, typename, typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_4  typename, typename, typename, typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_5  typename, typename, typename, typename, typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_6  typename, typename, typename, typename, typename, typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_7  typename, typename, typename, typename, typename, typename, typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_8  typename, typename, typename, typename, typename, typename, typename, typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_9  typename, typename, typename, typename, typename, typename, typename, typename, typename
#define STDBP_STD11_TEMPLATE_TYPENAMES_10 typename, typename, typename, typename, typename, typename, typename, typename, typename, typename

#define STDBP_STD11_TEMPLATE_ARGS_1   A0
#define STDBP_STD11_TEMPLATE_ARGS_2   A0, A1
#define STDBP_STD11_TEMPLATE_ARGS_3   A0, A1, A2
#define STDBP_STD11_TEMPLATE_ARGS_4   A0, A1, A2, A3
#define STDBP_STD11_TEMPLATE_ARGS_5   A0, A1, A2, A3, A4
#define STDBP_STD11_TEMPLATE_ARGS_6   A0, A1, A2, A3, A4, A5
#define STDBP_STD11_TEMPLATE_ARGS_7   A0, A1, A2, A3, A4, A5, A6
#define STDBP_STD11_TEMPLATE_ARGS_8   A0, A1, A2, A3, A4, A5, A6, A7
#define STDBP_STD11_TEMPLATE_ARGS_9   A0, A1, A2, A3, A4, A5, A6, A7, A8
#define STDBP_STD11_TEMPLATE_ARGS_10  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9

#define STDBP_STD11_FUNCTION_PARAMS_1   A0 a0
#define STDBP_STD11_FUNCTION_PARAMS_2   A0 a0, A1 a1
#define STDBP_STD11_FUNCTION_PARAMS_3   A0 a0, A1 a1, A2 a2
#define STDBP_STD11_FUNCTION_PARAMS_4   A0 a0, A1 a1, A2 a2, A3 a3
#define STDBP_STD11_FUNCTION_PARAMS_5   A0 a0, A1 a1, A2 a2, A3 a3, A4 a4
#define STDBP_STD11_FUNCTION_PARAMS_6   A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5
#define STDBP_STD11_FUNCTION_PARAMS_7   A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6
#define STDBP_STD11_FUNCTION_PARAMS_8   A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7
#define STDBP_STD11_FUNCTION_PARAMS_9   A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8
#define STDBP_STD11_FUNCTION_PARAMS_10  A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9

#define STDBP_STD11_FUNCTION_ARGS_1   a0
#define STDBP_STD11_FUNCTION_ARGS_2   a0, a1
#define STDBP_STD11_FUNCTION_ARGS_3   a0, a1, a2
#define STDBP_STD11_FUNCTION_ARGS_4   a0, a1, a2, a3
#define STDBP_STD11_FUNCTION_ARGS_5   a0, a1, a2, a3, a4
#define STDBP_STD11_FUNCTION_ARGS_6   a0, a1, a2, a3, a4, a5
#define STDBP_STD11_FUNCTION_ARGS_7   a0, a1, a2, a3, a4, a5, a6
#define STDBP_STD11_FUNCTION_ARGS_8   a0, a1, a2, a3, a4, a5, a6, a7
#define STDBP_STD11_FUNCTION_ARGS_9   a0, a1, a2, a3, a4, a5, a6, a7, a8
#define STDBP_STD11_FUNCTION_ARGS_10  a0, a1, a2, a3, a4, a5, a6, a7, a8, a9

#endif /* STDBP_STD11_INTERNAL_PSEUDO_VARIADIC_TEMPLATE_H_ */
