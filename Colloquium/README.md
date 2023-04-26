# Сolloquium

## Theme: «Design Patterns and Unit Testing»

### Overview

* Реализовать полноценный пример связки (совместной работы) двух Design Patterns,
разобранных на занятиях,
с описанием контекста в текстовом файле (само собой соответствующие контексту названия классов, методов).
* Покрыть их Unit Test-ами (и данными, соответствующими контексту)

### Контекст

Контекстом примера является контролируемая ASCII-анимация в консольном приложении, что-то вроде игры.

Имея наш игровой объект `actor` мы контролируем его поведение с помощью консольного ввода.

Ввод переключает 'состояние' нашего объекта. Потому и напрашивается распространенный в разработке игр,
а в частности ИИ, design pattern `State`. В общем случае этот шаблон не часто используют в паре с
`Template Method`, но в некоторых ситуациях их сочетание дает очень гибкую, расширяемую архитектуру:

* В случае когда мы имеем похожие состояния мы можем разложить их до одного базового с шаблонным `Update` методом
и переопределять его шаги вместо всего метода
* В случае когда `State` отвечает не только за управление состоянием, но и за его реализацию (например отрисовку,
физику и так далее)

Второй случай как раз про нашу игру, где мы не имеем ни какого-либо глобального render-менеджера, ни физического движка.
Возможно даже при таких скромных требованиях имеет смысл выделить эти процессы из нашего `State`, но
в рамках примера рассмотрим случай, когда мы не стали этого делать.

### Реализация

Реализация шаблона `State` заключается на самом деле в одном виртуальном методе: 

```cpp
State* State::Update(char input) {
    Move();
    Render();
    return HandleInput(input);
}
```

Конечно в нашем случае система ввода довольна проста и каждой клавише соответствует свое состояние, но в реальном случае конечно
переходы между состояними были бы гораздо сложнее, потому и метод `HandleInput` был бы переопределен для каждого состояния по-своему.

```cpp
State* State::HandleInput(char input) {
    switch (input) {
        case '3': {
            return new StateSad(actor_);
        }
        case '2': {
            return new StateHappy(actor_);
        }
        case '1': {
            return new StateIdle(actor_);
        }
        default: {
            return this;
        }
    }
}
```

Тут же во всех состояниях используется ввод `по умолчанию`. Этот ввод определяет следующее состояние в которое переходит наш объект путем того,
что метод `Update` возвращает указатель на новый `State-объект`.

Затем в 'Update' методе нашего Actor-объекта мы удаляем предыдущее состояние и переписываем указатель:

```cpp
void Actor::Update(char input) {
    State* next_state = state->Update(input);
    if (next_state != state) {
        delete state;
        state = next_state;
    }
}
```

Строку `state = next_state` стоило бы выделить в метод `ChangeState`, так как за этой сменой могла бы быть энкапсулирована логика смены анимаций,
изменения поведения ИИ и многое другое, но в нашем простом случае оставим как есть.

Так же отсюда видно, что нашим шаблонным методом мог бы стать и `Update` метод Actor-объекта, возможно в иных случаях более правильная реализация.
Мы же имеем `State`-объекты без собственного внутреннего состояния (переменных-членов), что тоже плюс.

```cpp
class State {
   public:
    State(Actor* actor);
    virtual ~State();
    State* Update(char input);

   protected:
    Actor* actor_;
    virtual void Render() = 0;
    virtual void Move() = 0;
    virtual State* HandleInput(char input);
};
```

Реализация `Template Method` как раз и заключается в 3 методах `Render`, `Move` и `HandleInput` - составляющих шагах `Update`-метода. Вероятно,
более правильно было бы выделить их реализацию в отдельные объекты, есть смысл задуматься об использовании паттерна `Strategy`.

**State Sad Implementation**

```cpp
void StateSad::Render() {
    const int y = actor_->y();
    const int x = actor_->x();
    string xoffset(x, ' ');
    // Draw the face at the current position
    cout << string(y, '\n');  // Move the cursor to the correct row
    cout << xoffset;          // Move the cursor to the correct column
    cout << "     _____     " << endl;
    cout << xoffset;
    cout << "  .'       '.  " << endl;
    cout << xoffset;
    cout << " /           \\ " << endl;
    cout << xoffset;
    cout << "|   0     0   | " << endl;
    cout << xoffset;
    cout << "|      ^      | " << endl;
    cout << xoffset;
    cout << "|  .     .    | " << endl;
    cout << xoffset;
    cout << "|  \\_____\\_/ | " << endl;
    cout << xoffset;
    cout << " \\          /  " << endl;
    cout << xoffset;
    cout << "  `-.___,-'   " << endl;
}

void StateSad::Move() {
    actor_->move(0, 2);
}
```

**State Happy Implementation**

```cpp
void StateHappy::Render() {
    const int y = actor_->y();
    const int x = actor_->x();
    string xoffset(x, ' ');
    // Draw the smile at the current position
    cout << string(y, '\n');  // Move the cursor to the correct row
    cout << xoffset;          // Move the cursor to the correct column
    cout << "     _____     " << endl;
    cout << xoffset;
    cout << "  .-'     `-.  " << endl;
    cout << xoffset;
    cout << " /           \\ " << endl;
    cout << xoffset;
    cout << "| o       o | " << endl;
    cout << xoffset;
    cout << "|           | " << endl;
    cout << xoffset;
    cout << "|  \\     /  | " << endl;
    cout << xoffset;
    cout << " \\  `---'  /  " << endl;
    cout << xoffset;
    cout << "  `-.___.-'   " << endl;
}

void StateHappy::Move() {
    actor_->move(3, 0);
}
```

Имеем две реализации шагов нашего шаблонного метода. Сравнив их, можно прийти к выводу, что в данной ситуации можно было бы обойтись вообще
без использования паттерна State, так как по факту реализации методов отличаются не вызовами функций, а разными используемыми `волшебными числами`.

Однако пример использовался с целью показать преимущества использования данных шаблонов. Преимущества становятся очевидными при появлении более сложных
и взаимозависимых изменений состояния.

### Возможные модификации

* Перенос `Template Method` в `Actor::Update`
* `ChangeState` - энкапсуляция смены состояния
* Разделение `Single State` на `RenderState, PhysicsState, InputState`
* `State + Template Method` -> `State + Strategy` (применимо в реальной разработке ИИ)
* `State Stack` или `Pushdown Automata` (хранение истории состояний)
* `Hierarchical State` - использовать наследование состояний в соотвутсвтующих случаях

### Unit-Testing

К сожалению, данный код сложно тестировать, так как он слишком упрощен в целях демонстрации работы паттерна.

Возможные тесты:

* E2E тесты управления - при идеальном проектировании система ввода должна легко меняться на автоматический ввод или ввод внешнего ИИ
* Unit-тесты физики - ну слишком абсурдный пример для unit-тестов, извините :)

### Usage

Author: Tsimafei Petrykevich

