#ifndef HEAD_H
#define HEAD_H

#define IN
#define VAR
#define OUT

enum Status: int
{
    success,
    err_load_file_incorrect,
    err_load_file_data_incorrect,
    err_load_file_data_empty,
    err_save_file_name_incorrect,
    err_model_empty,
    err_memory_allocation_error,
    err_unknown_action_type,
    err_projection_empty,
    err_data_incorrect
};

enum ActionType: int
{
    LOAD,
    SAVE,
    MOVE,
    SCALE,
    ROTATE,
    PROJECT,
    CLEAR_MODEL
};

struct MoveVector
{
    float dx;
    float dy;
    float dz;
};

struct RotationAngle
{
    float degX;
    float degY;
    float degZ;
};

struct Matrix
{
    float data[4][4];
};

struct Vector
{
    float data[4];
};

struct ScaleRatio
{
    float ratioX;
    float ratioY;
    float ratioZ;
};

struct Action
{
    ActionType type;
    union
    {
        MoveVector moveVector;
        RotationAngle rotationAngle;
        ScaleRatio scaleRatio;
        const char* filename;
    };
};

#endif // HEAD_H
