package com.changf.ndk;

import android.app.Activity;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.TextView;

import com.changf.ndk.lib.NativeMethed;
import com.squareup.leakcanary.RefWatcher;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import butterknife.Unbinder;

public class MainActivity extends Activity {

    private static final String TAG = "MainActivity";
    @BindView(R.id.tv_call_info)
    TextView tvCallInfo;
    @BindView(R.id.tv_value)
    TextView tvValue;
    @BindView(R.id.tv_array)
    TextView tvArray;
    Unbinder unbinder;

    private long value = 0;
    private int[] arr = {10, 20, 30};
    private String callJavaInfo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //绑定初始化ButterKnife
        unbinder = ButterKnife.bind(this);

        showValue();
        showArray();
        showCallJava();
    }

    private void showCallJava() {
        if(TextUtils.isEmpty(callJavaInfo)){
            tvCallInfo.setText("");
        }else{
            tvCallInfo.setText(callJavaInfo);
        }
    }

    private void showValue() {
        tvValue.setText("value的当前值为：" + value);
    }

    private void showArray() {
        StringBuffer sb = new StringBuffer();
        for (int a : arr) {
            sb.append("[");
            sb.append(String.valueOf(a));
            sb.append("]");
            sb.append(" ");
        }
        String content = sb.toString();
        if ("".equals(content)) {
            content = "[]";
        }
        tvArray.setText("array的当前值为：" + content);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbinder.unbind();
        RefWatcher refWatcher = MyApplication.getRefWatcher(this);//1
        refWatcher.watch(this);
    }

    @OnClick({R.id.btn_add, R.id.btn_minus, R.id.btn_multiply, R.id.btn_divide, R.id.btn_remind_array, R.id.btn_delete_array_value, R.id.btn_add_array_value
            ,R.id.btn_call_instance_method, R.id.btn_call_static_method,R.id.btn_call_instance_attr,R.id.btn_call_static_attr,R.id.btn_call_construct_method,R.id.btn_call_superclass_method})
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_add:
                value = NativeMethed.getInstance().add(value);
                showValue();
                break;
            case R.id.btn_minus:
                value = NativeMethed.getInstance().minus(value);
                showValue();
                break;
            case R.id.btn_multiply:
                value = NativeMethed.getInstance().multiply(value);
                showValue();
                break;
            case R.id.btn_divide:
                value = NativeMethed.getInstance().divide(value);
                showValue();
                break;
            case R.id.btn_remind_array:
                NativeMethed.getInstance().remindArray(arr);
                showArray();
                break;
            case R.id.btn_delete_array_value:
                arr = NativeMethed.getInstance().deleteArrayValue(arr);
                showArray();
                break;
            case R.id.btn_add_array_value:
                arr = NativeMethed.getInstance().addArrayValue(arr);
                showArray();
                break;
            case R.id.btn_call_instance_method:
                callJavaInfo = NativeMethed.getInstance().callInstanceMethod();
                showCallJava();
                break;
            case R.id.btn_call_static_method:
                callJavaInfo = NativeMethed.getInstance().callStaticMethod();
                showCallJava();
                break;
            case R.id.btn_call_instance_attr:
                callJavaInfo = NativeMethed.getInstance().callInstanceAttr();
                showCallJava();
                break;
            case R.id.btn_call_static_attr:
                callJavaInfo = NativeMethed.getInstance().callStaticAttr();
                showCallJava();
                break;
            case R.id.btn_call_construct_method:
                callJavaInfo = NativeMethed.getInstance().callConstructMethod().getConstructAttr();
                showCallJava();
                break;
            case R.id.btn_call_superclass_method:
                callJavaInfo = NativeMethed.getInstance().callSuperClassMethod();
                showCallJava();
                break;
        }
    }

}
