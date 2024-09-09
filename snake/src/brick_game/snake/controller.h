#ifndef CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_
#define CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_

#include "fsm.h"

namespace s21 {

/**
 * @brief Тонкий контроллер. Отвечает за передачу сигнала от интерфейса к логике
 * игры
 */
class Controller {
 public:
  /**
   * @brief Объект КА
   */
  SnakeStateMachine fsm;

  /**
   * @brief Передает в КА сигнал 'Up'
   */
  void up(bool hold);

  /**
   * @brief Передает в КА сигнал 'Down'
   */
  void down(bool hold);

  /**
   * @brief Передает в КА сигнал 'Left'
   */
  void left(bool hold);

  /**
   * @brief Передает в КА сигнал 'Right'
   */
  void right(bool hold);

  /**
   * @brief Передает в КА сигнал 'Terninate'
   */
  void terminate(bool hold);

  /**
   * @brief Передает в КА сигнал 'Pause'
   */
  void pause(bool hold);

  /**
   * @brief Передает в КА сигнал 'Action'
   */
  void action(bool hold);

  /**
   * @brief Передает в КА сигнал 'Start'
   */
  void start(bool hold);

  /**
   * @brief Передает на обработку прошлый известный сигнал. Выбирается при
   * отсутсвии или поступлении неизвестного сигнала
   */
  void currentAction(bool hold);
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_
