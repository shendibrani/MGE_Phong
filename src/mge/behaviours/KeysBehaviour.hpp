#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour : public AbstractBehaviour
{
	public:
		KeysBehaviour(float moveSpeed = 5, float turnSpeed = 45);
		virtual ~KeysBehaviour();
		virtual void update( float step );

    private:
        float _moveSpeed;
        float _turnSpeed;
};

#endif // KEYSBEHAVIOUR_H
