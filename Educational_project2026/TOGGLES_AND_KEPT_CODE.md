# ملاحظات: أجزاء معلّقة بالكود بقصد (مش منسية ولا زيادة)
# Notes: Intentionally Commented-Out Code (not forgotten, not dead weight)

هاد الملف بيوثّق كل مكان بالمشروع فيه كود **معلّق بقصد** (مش محذوف)، لأنو
محتاجينه بوقت من الأوقات. الهدف إنك تلاقيه بسرعة لما تحتاجه، بدل ما تدوّر
بكل الملفات.
This file documents every place in the project with code that is
**intentionally commented out** (not deleted), because it is still useful
at certain times. The goal is to let you find it quickly when needed,
instead of searching through every file.

---

## 1) `Educational_project2026.cpp` — مفتاح "شغّل التطبيق" أو "شغّل الاختبارات"
## 1) `Educational_project2026.cpp` — "Run the app" vs "Run the tests" switch

بـ `main()`، فيه متغيّر `bool runTestsInstead`:
In `main()`, there is a `bool runTestsInstead` variable:

- `true`  → بيشغّل `TestAdapters()` وكل اختبارات GoogleTest بدل التطبيق.
           → Runs `TestAdapters()` and the full GoogleTest suite instead of the app.
- `false` → بيشغّل التطبيق العادي (`StartApp()`).
           → Runs the normal application (`StartApp()`).

**وين تستخدمه:** لما بدك تتأكد إنو كل شي شغّال صح بعد أي تعديل كبير بالكود
(الـ Adapters، التحميل من الملفات، إلخ) قبل ما ترجع تشتغل بالتطبيق نفسه.
**When to use it:** whenever you want to confirm everything still works
correctly after a significant code change (adapters, file loading, etc.)
before going back to using the app itself.

---

## 2) `Menus/ProblemsMenu.cpp` — استدعاءات `Run()` المعلّقة
## 2) `Menus/ProblemsMenu.cpp` — commented-out `Run()` calls

فيه 3 أماكن فيها `//Run();` معلّقة (بعد تشغيل التمرين الافتراضي، بعد
اختيار تمرين، وبـ `RefreshProblemsMenu()`)، وواحدة `//nsAppController::...::StartApp();`
بخيار Set Default Problem.

There are 3 spots with a commented `//Run();` (after running the default
problem, after selecting a problem, and in `RefreshProblemsMenu()`), plus
one `//nsAppController::...::StartApp();` in the Set Default Problem option.

**ليش معلّقة:** هاي كانت السبب الأصلي لمشكلة الـ Stack Overflow (تحذير
`C4717`) - كل استدعاء كان عم يضيف طبقة جديدة فوق الستاك بدل ما يرجع
للحلقة `while(true)` الأصلية بـ `Run()`.
**Why commented out:** these were the original cause of the Stack Overflow
issue (`C4717` warning) - each call kept adding a new stack frame instead of
letting control return to the original `while(true)` loop in `Run()`.

**وين تحتاجها:** ما في داعي ترجعها أبداً بالوضع الحالي - الحلقة الأصلية
بتعمل نفس الغرض (ترجع للقائمة) بدون أي خطر. خليها معلّقة دايماً كمرجع
تاريخي بس.
**When you might need them:** you shouldn't ever need to re-enable them in
the current design - the original loop already achieves the same "return
to menu" behavior safely. Keep them commented as historical reference only.

---

## 3) `DataInserters/ProblemInserter.cpp` — تعليق إضافة التمرين لملف `.vcxproj`
## 3) `DataInserters/ProblemInserter.cpp` — commented .vcxproj-append logic

فيه بلوك معلّق بالكامل (مسارات + استدعاء كان لـ `VcxprojUpdater::AppendFiles`،
اللي هلق محذوف بالكامل من المشروع) بيوضّح إنو التمارين ما عادت تُضاف
لملف المشروع الرئيسي - خليناه كتوثيق لتاريخ القرار، مش لأنو محتاج يرجع.

There is a fully-commented block (paths + a call that used to go to
`VcxprojUpdater::AppendFiles`, now fully removed from the project) that
documents that exercises are no longer added to the main project file -
kept as documentation of the decision's history, not because it needs to
come back.

---

## أجزاء انحذفت نهائياً (مش موجودة ولا حتى معلّقة)
## Parts removed completely (not even kept commented)

هاي كانت فعلياً مش مستخدمة بأي تدفّق حالي بالمشروع، فانحذفت بالكامل:
These were genuinely unused in any current project flow, so they were
deleted entirely:

- `VcxprojUpdater/` (الكلاس كامل - كان يضيف/يحذف ملفات من `.vcxproj`)
- `Registry/DispatcherRegistrar.hpp` و`Registry/DispatcherRunner.hpp`
  (نظام تشغيل التمارين القديم جوا نفس الـ exe - استبدله `ProblemCompiler`)
- `DataRunner/ProblemRunner.cpp`/`.hpp` (دالة `RunProblem()` ما كانت
  منادية من أي مكان)
- تمرين الاختبار `c01Problem009` (كان تجريبي بس للفحص)
