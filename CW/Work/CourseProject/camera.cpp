#include "camera.h"

Camera::Camera()
{

}

void Camera::rotate(Vector3 delta)
{
    Matrix rotationMatrix;

    rotationMatrix = formRotateMatrix(delta);

    rotation_ += delta;
    if (rotation_.x_ >= (2 * M_PI))
        rotation_.x_ = rotation_.x_ - (2 * M_PI);
    if (rotation_.y_ >= (2 * M_PI))
        rotation_.y_ = rotation_.y_ - (2 * M_PI);
    if (rotation_.z_ >= (2 * M_PI))
        rotation_.z_ = rotation_.z_ - (2 * M_PI);
    if (rotation_.x_ <= -(2 * M_PI))
        rotation_.x_ = rotation_.x_ + (2 * M_PI);
    if (rotation_.y_ <= -(2 * M_PI))
        rotation_.y_ = rotation_.y_ + (2 * M_PI);
    if (rotation_.z_ <= -(2 * M_PI))
        rotation_.z_ = rotation_.z_ + (2 * M_PI);


    right_.vdot(rotationMatrix);
    up_.vdot(rotationMatrix);
    lookDir_.vdot(rotationMatrix);
}

void Camera::move(Vector3 delta)
{
    position_ = position_ + delta;
}

void Camera::localRotation(Vector3 delta)
{
    Matrix localRotationMatrix;
    localRotationMatrix = formRotateMatrix(delta);
    Matrix rotationMatrix;
    Vector3 oldRotation = rotation_;
    Vector3 backToOriginal = rotation_ * -1;
    rotationMatrix = formRotateMatrix(backToOriginal);

    localRotation_ += delta;
    if (localRotation_.x_ >= (2 * M_PI))
        localRotation_.x_ = localRotation_.x_ - (2 * M_PI);
    if (localRotation_.y_ >= (2 * M_PI))
        localRotation_.y_ = localRotation_.y_ - (2 * M_PI);
    if (localRotation_.z_ >= (2 * M_PI))
        localRotation_.z_ = localRotation_.z_ - (2 * M_PI);
    if (localRotation_.x_ <= -(2 * M_PI))
        localRotation_.x_ = localRotation_.x_ + (2 * M_PI);
    if (localRotation_.y_ <= -(2 * M_PI))
        localRotation_.y_ = localRotation_.y_ + (2 * M_PI);
    if (localRotation_.z_ <= -(2 * M_PI))
        localRotation_.z_ = localRotation_.z_ + (2 * M_PI);

    // Rotate to zero
    right_.vdot(rotationMatrix);
    up_.vdot(rotationMatrix);
    lookDir_.vdot(rotationMatrix);

    // Rotate delta
    rotationMatrix = formRotateMatrix(delta);

    right_.vdot(rotationMatrix);
    up_.vdot(rotationMatrix);
    lookDir_.vdot(rotationMatrix);

    // Rotate back
    rotationMatrix = formRotateMatrix(oldRotation);

    right_.vdot(rotationMatrix);
    up_.vdot(rotationMatrix);
    lookDir_.vdot(rotationMatrix);
}

Vector3 Camera::formVectorToPosition(Vector3 position)
{
    return position - position_;
}

Vector3 Camera::formVectorToPositionNormalized(Vector3 position)
{
    Vector3 vector = formVectorToPosition(position);
    return vector / vector.magnitude();
}

Matrix Camera::formViewMatrix()
{
    Vector3 target = position_ + lookDir_;
    Matrix camMatrix;
    pointAtMatrix(position_, target, up_, camMatrix);
    Matrix viewMatrix;
    viewMatrix = camMatrix.inverse_4x4();
    return viewMatrix;
}

void Camera::pointAtMatrix(Vector3 &pos, Vector3 &target, Vector3 &up, Matrix &result)
{
    Vector3 forward = (target - pos).normalized();
    Vector3 a = forward * up.scalar(forward);
    Vector3 newUp = (up - a).normalized();

    Vector3 newRight = newUp.vector(forward);

    result.data_[0][0] = newRight.x_; result.data_[0][1] = newRight.y_; result.data_[0][2] = newRight.z_; result.data_[0][3] = 0.0f;
    result.data_[1][0] = newUp.x_; result.data_[1][1] = newUp.y_; result.data_[1][2] = newUp.z_; result.data_[1][3] = 0.0f;
    result.data_[2][0] = forward.x_; result.data_[2][1] = forward.y_; result.data_[2][2] = forward.z_; result.data_[2][3] = 0.0f;
    result.data_[3][0] = pos.x_; result.data_[3][1] = pos.y_; result.data_[3][2] = pos.z_; result.data_[3][3] = 1.0f;
}

void Camera::scale(Vector3 koef)
{

}
