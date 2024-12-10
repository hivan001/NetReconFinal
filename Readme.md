# Net Recon
Network Mapping Tool

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)

## Installation
1. Clone the repo:
```bash
git clone https://github.com/hivan001/NetReconFinal.git
```

2. Create the virtual environment
```bash
mkdir net_recon
cd net_recon
python3 -m venv venv
source venv/bin/activate
```
This creates a net_recon directory and creates/activates the virtual environment

3. Install dependencies: 
```python
pip install -r requirements.txt
```

## Usage

1. To run the project, navigate to the bin directory and run the executable
```bash
cd bin
./net_recon
```

2. Net Recon accepts command line arguments to determine the type of scan that you'd like to run. -t runs a TCP scan while -u runs a UDP scan. 


![Alt Text - running Net Recon](/scan/screenshots/net_recon_run.png)

3. While the scan is running the output will be displayed in the terminal

![Alt Text - running Net Recon](/scan/screenshots/net_recon_output.png)


4. After the scan is complete, the gui will populate with the results of the scan

![Alt Text - running Net Recon](/scan/screenshots/net_recon_gui.png)











