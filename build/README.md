# Memory viewer features

## Increment/Decrement with +/-
Use numpad + and - to increment decrement values directly in the memory viewer.
\
Min/max tresholds prevent to exceed min/max value of the selected address.
* Increment/decrement by 1 : **NumPad +/-** 
* Increment/decrement by 4 : **CTRL + NumPad +/-**
* Increment/decrement by 8 : **SHIFT + NumPad +/-**
* Increment/decrement by 16 : **CTRL + SHIFT + NumPad +/-**

## Copy/Paste
You can copy and paste value directly in the memory viewer.
* Copy selected address value : **CTRL + C**
* Paste clipboard value in the selected address : **CTRL + V** (Replace mode)
\
**Replace mode** means that the pasted value will replace the actual value at the selected address \
Examples : 
\
```copy "00000123" into "12345678" => "00000123"```
\
```copy "123" into "12345678" => "12345123"```
\
With this mode, you can paste very long value and it will replace all the required bytes.
\
```copy "12345678123456781234567812345678" @ address 0x001230 will replace all value between 0x001230 and 0x00123f```
* Paste clipboard value in the selected address : **CTRL + SHIFT + V** (Strict mode)
\
**Strict mode** means that the pasted value will only cover the selected byte(s) \
Examples :
\
```copy "12345678" into 32-bit address containing "12345678" => "12345678"```
\
```copy "123" into 32-bit address containing "12345678" => "00000123"```
\
```copy "12345678" into 16-bit address containing "1234" => "5678"```
\
```copy "12345678" into 8-bit address containing "12" => "78"```
\
With this mode, you never oveflow the selected address and values are adjusted to fit into it.
\

## Pointer follower
**Shift + click** on a 32-bit address will move the focus to the targetted address (if in the range of the console memory)
\
Example :  **Shift + click** on address **0x80123456** on Playstation will change the current address to **0x123456** which maybe will contain another pointer that you will be able to **shift + click** too and continue to quickly investigate where it goes.
