from setuptools import find_packages, setup

package_name = 'roverbrain_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='rover',
    maintainer_email='rover@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "receiver = roverbrain_pkg.controller_receiver:main",
            "motor_control = roverbrain_pkg.motor_control:main",
            "steering_control = roverbrain_pkg.steering_control:main"

        ],
    },
)
