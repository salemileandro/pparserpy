import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="pyrserpp-LEANDRO", # Replace with your own username
    version="0.0.2",
    author="Leandro Salemi",
    author_email="salemileandro@gmail.com",
    description="A simple utility to generate C++ parsing tool",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://google.com",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.4',
    include_package_data=True,
)

