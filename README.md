<h1>Анишкин дифференциатор</h1>
<h2>Что он делает?</h2>
<p>Вы можете использовать эту программу для вычисления n-ой производной, получения ряда маклорена n-ой степени и построения графика для получившихся выражений.</p>

<h2>Какой принцип работы?</h2>
<h3>1. Создание дерева</h3>
<p>Программа принимает на вход файл с выражением в виде строки. Это выражение имеет определенную структуру. <b>Например:</b></p>
```
sin(x)+x^2#
```
<p>Символ <b>#</b> означает конец выражения. Символы после этого знака обрабатываться не будут.</p>
<p>На основании этого выражения sin(x)+x² строится бинарное дерево:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/tree1.jpeg" width=450px>
<p>Операции, которые расознает программа:</p>
<ul>
 <li>sin(x)</li>
 <li>cos(x)</li>
 <li>ln(x)</li>
 <li>ch(x)</li>
 <li>sh(x),</li>
</ul>
<p>а так же константа pi и exp</p>

<h3>2.1. Дифференцирование</h3>
<p>Этот алгоритм использует рекурсию для преобразования каждого узла особым образом. В итоге мы получим дерево дифференцированной функции. <b>Для примера выше</b> дерево после взятия производной будет выглядеть таким образом:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/tree2.jpeg" width=450px>
<p>Если требуется дифференцирование степени выше единицы, то алгоритм используется повторно для полученного дерева.</p>

<h3>2.2. Получение ряда Маклорена</h3>
<p>Для получение ряда Маклорена используется алгоритм из <b>пункта 2.1</b>. Далее мы вместо переменной мы подставляем 0 и умножаем уравнение на x в степени дифференцирования. Так мы получаем n деревьев, которые объединяем суммированием. <b>Для примера выше</b> ряд Маклорена 1-ой степени:</p>

<h3>3. Оптимизация</h3>
<p>Часто после выполнения <b>пункта 2</b> получаются очень объемные деревья. Именно поэтому для удобства чтения деревья оптимизируются. <b>Примеры моих оптимизаций:</b></p>
<ul>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt1.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt2.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt3.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt4.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt5.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt6.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt7.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt8.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt9.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt10.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt11.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt12.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt13.jpeg" width=300px></li>
 <li><image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/opt14.jpeg" width=300px></li>
</ul>
<h2>Как запустить программу?</h2>
''''
make
''''
<p>Вторым аргументом в данной команде вводится файл с выражением, иначе будет обрабатываться файл по-умолчанию:</p>
''''
./main_
''''
<p>Предлагается выбрать один из модов:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/console1.jpeg" width=450px>
<p>В режиме дифференцирования предлагается ввести степень дифференцирования:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/console2.jpeg" width=450px>
<p>В режиме Маклорена предлагается ввести степень ряда Маклорена:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/console3.jpeg" width=450px>
<p>При неверном вводе мода выводится ошибка:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/console4.jpeg" width=450px>
<p>Ввод продолжается до тех пор, пока пользователь не введет <b>exit</b>:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/console5.jpeg" width=450px>
<h2>Как выглядит результат работы программы?</h2>

<p>В tex-файл по-очереди выписываются для каждой команды:</p>
<ul>
 <li>Изначальный вид выражения</li>
 <li>Выражение после выполения алгоритма</li>
 <li>Оптимизированный вид измененного выражения</li>
 <li>График выражения до и после работы программы</li>
</ul>

<p>Для выражения sin(x)+x² результат дифференцирования 1-ой степени будет иметь такой вид:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/example1.jpeg" width=450px>

<p>А для разложения в ряд Маклорена 3-ой степени будет иметь такой вид:</p>
<image src="https://github.com/arutiunianan/Differentiator/blob/main/for_readme/example2.jpeg" width=450px>