#include "Definitions.h"

volatile char userInput = 0;

const char arrowLeft[8] = {         // Arrow facing up character data            */
  0b00000010,                                // 1st row          _____*__                 */
  0b00000100,                                // 2nd row          ____***_                 */
  0b00001000,                                // 3rd row          ___*_*_*                 */
  0b00010000,                                // 4th row          _____*__                 */
  0b00001000,                                // 5th row          _____*__                 */
  0b00000100,                                // 6th row          _____*__                 */
  0b00000010,                                // 7th row          _____*__                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
}; 
const char arrowRight[8] = {         // Arrow facing up character data            */
  0b00001000,                                // 1st row          _____*__                 */
  0b00000100,                                // 2nd row          ____***_                 */
  0b00000010,                                // 3rd row          ___*_*_*                 */
  0b00000001,                                // 4th row          _____*__                 */
  0b00000010,                                // 5th row          _____*__                 */
  0b00000100,                                // 6th row          _____*__                 */
  0b00001000,                                // 7th row          _____*__                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
}; 