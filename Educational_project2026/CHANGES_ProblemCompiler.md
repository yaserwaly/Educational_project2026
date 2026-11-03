# تعديلات هذه النسخة التجريبية — فصل بناء التمارين عن المشروع الرئيسي

## المشكلة الأصلية
كل تمرين جديد كان يُضاف مباشرة كـ `<ClCompile>` داخل
`Educational_project2026.vcxproj` (عبر `VcxprojUpdater::AppendFiles`),
فأي Build كان يعيد فحص/ترجمة/ربط كل التمارين الموجودة — وبيصير أبطأ
كل ما زاد عددها.

## التعديل
1. **ملف جديد:** `Compiler/ProblemCompiler.hpp` و `Compiler/ProblemCompiler.cpp`
   - يولّد ملف `main()` صغير مؤقت بمجلد `Temp/`
   - يبني هذا الملف + ملف التمرين فقط (سطر واحد عبر `cl.exe`)
   - يشغّل الملف الناتج مباشرة

2. **`Menus/ProblemsMenu.cpp`**: استبدال نداءي
   `DispatcherRunner::Run(...)` بنداء
   `ProblemCompiler::CompileAndRun(FilePath, Namespace)` — البيانات
   مأخوذة من `sProblemData` (كانت موجودة أصلاً).

3. **`DataInserters/ProblemInserter.cpp`**:
   - تعطيل استدعاء `VcxprojUpdater::AppendFiles` (التمرين الجديد ما عاد
     ينضاف لـ .vcxproj، بس يبقى على القرص ويوثّقه `Logic_Files.txt`).
   - تبسيط محتوى ملف الـ .cpp المولَّد (حذف تسجيل `DispatcherRegistrar`
     غير اللازم بعد الآن).

4. **`Educational_project2026.vcxproj` / `.vcxproj.filters`**:
   - إضافة `Compiler/ProblemCompiler.cpp/.hpp` للمشروع الرئيسي.
   - حذف التمارين الثمانية الموجودة (`c01Problem001..008`) من قوائم
     `ClCompile` / `ClInclude` — صارت تُبنى لحالها عند الطلب فقط.

## مهم قبل التجربة
`ProblemCompiler` بينادي `cl.exe` مباشرة عبر `system()`، فلازم تشغّل
التطبيق من **Developer Command Prompt for VS** (أو تتأكد إنو
`cl.exe` موجود على الـ PATH)، وإلا الأمر رح يفشل. إذا بتفضّل
MinGW/g++ بدل MSVC، بدّل سطر الأمر بـ `Compiler/ProblemCompiler.cpp`
(في تعليق جاهز بالملف يوضح البديل).

## النتيجة المتوقعة
- بناء المشروع الرئيسي (F7) بيصير بزمن شبه ثابت مهما زاد عدد التمارين.
- تشغيل تمرين معيّن (من قائمة Problems) بيبني بس ملفّه هو (+ wrapper
  صغير) وبيشغّله مباشرة — ثواني قليلة بدل إعادة بناء كل شي.

## تحديث: تفعيل بيئة MSVC تلقائياً (بدون Developer Command Prompt)

`ProblemCompiler.cpp` صار يلاقي تثبيت Visual Studio تلقائياً عبر
`vswhere.exe` (مرفق دائمًا مع أي تنصيب VS)، وبعدين يحمّل بيئة MSVC عبر
`vcvarsall.bat` بنفس أمر البناء — فـ`cl.exe` بيصير متوفر لحاله مهما
كانت الطريقة اللي شغّلت فيها التطبيق (حتى زر Start بـ Visual Studio
نفسه)، وما عاد في داعي لـ Developer Command Prompt يدوياً.

**شرط وحيد:** يكون عندك workload **"Desktop development with C++"**
مثبّت (موجود أصلاً إذا قدرت تبني المشروع نفسه من الأساس).

## تحديث ثاني: حل مشكلة الأقواس بمسار "Program Files (x86)"

`vswhere.exe` موجود دايمًا بمسار فيه أقواس حرفية: `C:\Program Files (x86)\...`.
`cmd.exe` عنده مشكلة معروفة: لما سطر الأمر فيه توكن واحد بس محاط
بعلامتَي تنصيص وجوّاه أقواس `()`، بيرفض يحافظ على التنصيص بشكل صحيح
(قاعدة خاصة موثّقة بـ cmd نفسه)، فبيطلع خطأ زي
`'C:\Program' is not recognized...`.

**الحل:** تغليف السطر كامل (الأمر + كل الباراميترات) بزوج إضافي من
علامات التنصيص من بره (double-quote wrap)، بدل التنصيص على المسار
لحاله بس. هذا أسلوب معروف ومستخدم تقليديًا لنفس هالمشكلة بالضبط مع
`cmd.exe` على ويندوز. اتطبّق نفس الأسلوب على استدعاء `vswhere.exe`
واستدعاء `cl.exe` الفعلي كمان (احتياطًا).
