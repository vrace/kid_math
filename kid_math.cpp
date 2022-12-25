#include <iostream>
#include <chrono>
#include <random>
#include <memory>

class MathQuiz
{
public:
    MathQuiz();
    virtual ~MathQuiz() = default;
    virtual void generate() = 0;

protected:
    std::mt19937 mt_;
};

MathQuiz::MathQuiz()
    : mt_(std::chrono::steady_clock::now().time_since_epoch().count())
{
}

////////////////////////////////////////////////////////////////////////////////

class MathQuizAdd10 : public MathQuiz
{
public:
    MathQuizAdd10();
    void generate() override;

private:
    std::uniform_int_distribution<> d_;
};

MathQuizAdd10::MathQuizAdd10()
    : MathQuiz()
    , d_(0, 9)
{
}

void MathQuizAdd10::generate()
{
    int a = d_(mt_);
    int b = d_(mt_);
    if (a < b) {
        std::swap(a, b);
    }
    int c = a - b;
    std::cout << c << " + " << b << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

class MathQuizAddSub : public MathQuiz
{
public:
    MathQuizAddSub(int num_max);
    void generate() override;

private:
    std::uniform_int_distribution<> d_;
};

MathQuizAddSub::MathQuizAddSub(int num_max)
    : MathQuiz()
    , d_(0, num_max)
{
}

void MathQuizAddSub::generate()
{
    int a = d_(mt_);
    int b = d_(mt_);
    if (a < b) {
        std::swap(a, b);
    }

    int m = mt_() % 2;
    if (m == 0) {
        std::cout << (a - b) << " + " << b << std::endl;
    }
    else {
        std::cout << a << " - " << b << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////

class MathQuizSubHard : public MathQuiz
{
public:
    MathQuizSubHard();
    void generate() override;

private:
    std::uniform_int_distribution<> da_;
};

MathQuizSubHard::MathQuizSubHard()
    : MathQuiz()
    , da_(11, 99)
{
}

void MathQuizSubHard::generate()
{
    int a = da_(mt_);
    int b = mt_() % (a / 10);
    int c = (a % 10);
    c += mt_() % (10 - c);

    std::cout << a << " - " << b * 10 + c << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::unique_ptr<MathQuiz> quiz = std::make_unique<MathQuizAddSub>(20);
    for (int i = 0; i < 12; i++) {
        quiz->generate();
    }
    
    return 0;
}
