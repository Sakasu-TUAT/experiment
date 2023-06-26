/*
エミュレータの情報
*/

#if !defined _EMULATER_H_
#define _EMULATER_H_

typedef enum p386_state_ {
  P386_STATE_INIT,  /* 未開始 */
  P386_STATE_RUNNING,  /* 実行中 */
  P386_STATE_INT,  /* 割り込み処理中 */
  P386_STATE_UNKINT,  /* 不明な割り込みにより停止 */
  P386_STATE_ILINST,  /* 不正なコードにより停止 */
  P386_STATE_HALT,  /* HLT 命令が実行され停止 */
  P386_STATE_UNSRPT  /* 未サポートの機能を実行しようとして停止 */
} p386_state_t;

#endif /* _EMULATER_H_ */
